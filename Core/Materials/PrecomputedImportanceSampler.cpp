/*
 * H-RT Core - the core of the H-RayTracer ray tracing renderer.
 * Copyright (c) Patryk Bajer, H-RT.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include "stdafx.h"
#include "PrecomputedImportanceSampler.h"
#include <unordered_map>
#include <iostream>
#include <fstream>

namespace Hrt
{
	typedef std::tr1::unordered_map<std::string, weak_ptr<PrecomputedImportanceSampler>> sampling_cache;
	sampling_cache s_samplingCache;

	size_t elevationSteps = 180;
	size_t azimuthSteps = 181;
  const char fileHeader[] = "!BCF";

  struct BrdfFileHeader
  {
    char IDTag[4];
    short int MajorVersion;
    short int MinorVersion;
    int ElevationSteps;
    int AzimuthSteps;
    char Reserved[16];

    BrdfFileHeader() 
    {
      std::fill(&Reserved[0], &Reserved[16], 0);
      std::copy(&fileHeader[0], &fileHeader[4], &IDTag[0]);
      MajorVersion = 0x02;
      MinorVersion = 0x04;
      ElevationSteps = elevationSteps;
      AzimuthSteps = azimuthSteps;
    }

    bool operator ==(const BrdfFileHeader& other) const
    {
      return MajorVersion == other.MajorVersion
        && MinorVersion == other.MinorVersion
        && std::equal(&IDTag[0], &IDTag[4], &other.IDTag[0])
        && ElevationSteps == other.ElevationSteps
        && AzimuthSteps == other.AzimuthSteps;
    }

    bool operator !=(const BrdfFileHeader& other) const
    {
      return !(*this == other);
    }
  };

  BrdfFileHeader CorrectHeader;
	const number elevationStep = Consts::HalfPi / elevationSteps;
	const number azimuthStep = Consts::TwoPi / azimuthSteps;

	static std::string SignatureToFilename(const std::string& signature, const std::string& ext)
	{
		size_t p = std::string::npos;
		std::string fn(signature);

		while ((p = fn.find_first_of(':')) != std::string::npos)
			fn[p] = '-';

		return fn + ext;
	}


	//
	// ---
	//

	PrecomputedImportanceSampler::PrecomputedImportanceSampler()
    : m_isPrepared(false)
	{
	}

	Vector3D PrecomputedImportanceSampler::SampleVector(number* sample, const Vector3D& outgoingDirection, 
		const Vector3D& tangentU, const Vector3D& tangentV, 
		const Vector3D& n, number& pdf, LightingType::Enum& lightingType)
	{
    lightingType = LightingType::AllReflection;

		// NOTE: this is actually much better than: m_random.RandomEndOpen(0, 1) for non-RandomSampler level samplers of course
		number v = (sample[0]+sample[1])/2;

		size_t index = (size_t)Math::Floor(outgoingDirection.Dot(n) * elevationSteps);

		std::vector<number>::iterator match = std::lower_bound(angleCdfs[index]->Cdf.begin(), angleCdfs[index]->Cdf.end(), v);
		size_t matchIndex = match - angleCdfs[index]->Cdf.begin();

		size_t elevationIndex = matchIndex / azimuthSteps;
		size_t azimuthIndex = matchIndex % azimuthSteps;
    pdf = angleCdfs[index]->Values[matchIndex];

    if (elevationIndex == index)
    {
      number ratio = angleCdfs[index]->IdealSpecularValue / pdf;
      if (v < ratio)
      {
        lightingType = static_cast<LightingType::Enum>(lightingType | LightingType::IdealSpecular);
        return outgoingDirection.Reflect(n);
      }
      else
        pdf -= angleCdfs[index]->IdealSpecularValue;
    }

		number inElevation = Math::Arcos(num(elevationIndex + sample[0]) / elevationSteps);
		number inAzimuth = num(azimuthIndex + sample[1]) * azimuthStep;

		// transform to a proper space
		if (outgoingDirection.Dot(n) < 1-epsilon)
		{
			Vector3D sv = n.Cross(outgoingDirection).Normalize();
			Vector3D su = sv.Cross(n).Normalize();
			return Vector3D::FromSpherical(inAzimuth, inElevation, su, sv, n);
		}
		else
		{
			return Vector3D::FromSpherical(inAzimuth, inElevation, tangentU, tangentV, n);
		}
	}

	void PrecomputedImportanceSampler::Precompute(MaterialPtr material)
	{
    if (m_isPrepared)
      return;

		std::string materialSignature = material->GetSignature();
		sampling_cache::iterator match = s_samplingCache.find(materialSignature);
		if (match != s_samplingCache.end())
		{
			shared_ptr<PrecomputedImportanceSampler> cached = (*match).second.lock();
			if (cached != 0)
			{
				angleCdfs = cached->angleCdfs;
        m_isPrepared = true;
				return;
			}
		}

		// try loading from file
		if (TryLoadFromFile(materialSignature))
		{
			s_samplingCache[materialSignature] = shared_from_this();
			return;
		}

		Intersection intersection;
		intersection.Normal = Vector3D::UnitZ;
		intersection.TangentU = Vector3D::UnitX;
		intersection.TangentV = Vector3D::UnitY;

		number hf = (azimuthSteps*elevationSteps)/Consts::TwoPi;

		std::cout << "Precomputing importance sampling for " << material->GetSignature() << std::endl;
		for(size_t i = 0; i < elevationSteps; i++)
		{
			// std::cout << (int)(100*(i+1)/num(elevationSteps)) << "%  \r";
			number cdf = 0;

			number outElevation = Math::Arcos(num(i + 0.5) / elevationSteps);
			intersection.RayDirection.Set(-Math::Sin(outElevation), 0, -Math::Cos(outElevation));

			shared_ptr<AnglePrecalc> precalc(new AnglePrecalc);
			for(size_t j = 0; j < elevationSteps; j++)
			{
				number inElevation = Math::Arcos(num(j + 0.5) / elevationSteps);
				number inElevationCos = Math::Cos(inElevation);
				number inElevationSin = Math::Sin(inElevation);

				for(size_t k = 0; k < azimuthSteps; k++)
				{
					number inAzimuth = (k + 0.5) * azimuthStep;
					number inAzimuthCos = Math::Cos(inAzimuth);
					number inAzimuthSin = Math::Sin(inAzimuth);

					RayLight incomingRay;
					incomingRay.Direction.Set( -inElevationSin * inAzimuthCos,
						-inElevationSin * inAzimuthSin,
						-inElevationCos);
					incomingRay.Radiance.SetOne();

          bool isIdealReflection = i == j && inAzimuth == Consts::Pi;

          LightingType::Enum lightingType = static_cast<LightingType::Enum>(isIdealReflection 
            ? LightingType::AllReflection | LightingType::IdealSpecular 
            : LightingType::AllReflection);
					number v = (material->CalculateBsdf(incomingRay, intersection, lightingType) 
						* Math::Abs(incomingRay.Direction.Z)).GetAverage();
					cdf += v;

          if (isIdealReflection)
          {
            precalc->IdealSpecularValue = v - (material->CalculateBsdf(incomingRay, intersection, LightingType::AllReflection)
              * Math::Abs(incomingRay.Direction.Z)).GetAverage();

            // std::cout << precalc->IdealSpecularValue << " / " << v;
          }

					precalc->Values.push_back(v);
					precalc->Cdf.push_back(cdf);
				}
			}

      // std::cout << " / " << cdf << std::endl;

			if (cdf == 0)
			{
				number spread = azimuthSteps*elevationSteps;
				for(std::vector<number>::iterator it = precalc->Cdf.begin(); it != precalc->Cdf.end(); it++)
					(*it) = 1;

				for(std::vector<number>::iterator it = precalc->Values.begin(); it != precalc->Values.end(); it++)
					*it = spread/hf;
			}
			else
			{
				for(std::vector<number>::iterator it = precalc->Cdf.begin(); it != precalc->Cdf.end(); it++)
					*it /= cdf;

				for(std::vector<number>::iterator it = precalc->Values.begin(); it != precalc->Values.end(); it++)
					*it /= (cdf/hf);

        precalc->IdealSpecularValue /= (cdf/hf); // to be comparable to PDF values
			}

			angleCdfs.push_back(precalc);
		}		

		SaveToFile(materialSignature);

		s_samplingCache[materialSignature] = shared_from_this();
    m_isPrepared = true;
	}

	bool PrecomputedImportanceSampler::TryLoadFromFile(const std::string& materialSignature)
	{
		try
		{
			std::string fileName = SignatureToFilename(materialSignature, ".brdf");
			std::ifstream inFile(fileName.c_str(), std::ifstream::binary);
			size_t tableSize = azimuthSteps*elevationSteps;

      // read and check header
      BrdfFileHeader header;
      inFile.read(reinterpret_cast<char*>(&header), sizeof(header));
      if (inFile.fail() || header != CorrectHeader) return false;

			// std::cout << "Loading importance sampling for " << materialSignature << "... ";

			for(size_t i = 0; i<elevationSteps; i++)
			{
				shared_ptr<AnglePrecalc> precalc(new AnglePrecalc);
				precalc->Values.resize(tableSize);
				precalc->Cdf.resize(tableSize);

				inFile.read(reinterpret_cast<char*>(&precalc->Values[0]), tableSize*sizeof(number));
				if (inFile.fail())
					throw 1;
				inFile.read(reinterpret_cast<char*>(&precalc->Cdf[0]), tableSize*sizeof(number));
				if (inFile.fail())
					throw 1;
        inFile.read(reinterpret_cast<char*>(&precalc->IdealSpecularValue), sizeof(number));
        if (inFile.fail())
          throw 1;

				angleCdfs.push_back(precalc);
			}

			// std::cout << "done" << std::endl;
			return true;
		}
		catch(...)
		{
			// std::cout << "failed" << std::endl;
      std::cerr << "Failed to load importance sampling for " << materialSignature << std::endl;
			return false;
		}
	}

	void PrecomputedImportanceSampler::SaveToFile(const std::string& materialSignature)
	{
		std::string fileName = SignatureToFilename(materialSignature, ".brdf");

		std::ofstream outFile(fileName.c_str(), std::ofstream::binary);
		size_t tableSize = azimuthSteps*elevationSteps;

    // write header
    outFile.write(reinterpret_cast<char*>(&CorrectHeader), sizeof(CorrectHeader));

		for(size_t i = 0; i<elevationSteps; i++)
		{
			shared_ptr<AnglePrecalc> precalc = angleCdfs[i];
			outFile.write(reinterpret_cast<char*>(&precalc->Values[0]), tableSize*sizeof(number));
			outFile.write(reinterpret_cast<char*>(&precalc->Cdf[0]), tableSize*sizeof(number));
      outFile.write(reinterpret_cast<char*>(&precalc->IdealSpecularValue), sizeof(number));
		}		
	}

	Hrt::number PrecomputedImportanceSampler::GetPdf(const Vector3D& incomingDirection, const Vector3D& outgoingDirection, const Vector3D& tangentU, const Vector3D& tangentV, const Vector3D& n, const LightingType::Enum lightingType)
	{
		number outElevation = acos(outgoingDirection.Dot(n));

		Vector3D sv, su;
		if (outgoingDirection.Dot(n) < 1-epsilon)
		{
			sv = n.Cross(outgoingDirection).Normalize();
			su = sv.Cross(n).Normalize();
		}
		else
		{
			su = tangentU;
			sv = tangentV;
		}

		number z = n.Dot(-incomingDirection);
		if (z < 0)
			return 0;

		number x = su.Dot(-incomingDirection);
		number y = sv.Dot(-incomingDirection);

		number inElevation = acos(z);
		number inAzimuth = atan2(y, x);

		if (inAzimuth < 0)
			inAzimuth += Consts::TwoPi;

		int inElevationIndex = (int)(inElevation / elevationStep);
		int inAzimuthIndex = (int)(inAzimuth / azimuthStep);
		int outElevationIndex = (int)(outElevation / elevationStep);

		return angleCdfs[Math::Min(elevationSteps-1, outElevationIndex)]->Values[inElevationIndex*azimuthSteps + inAzimuthIndex];
	}
}
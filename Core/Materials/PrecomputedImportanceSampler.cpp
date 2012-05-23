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

	const int outElevationSteps = 180;
	const int inElevationSteps = 180;
	const int inAzimuthSteps = 180;

	const number outElevationStep = Consts::HalfPi / outElevationSteps;
	const number inElevationStep = Consts::HalfPi / inElevationSteps;
	const number inAzimuthStep = Consts::TwoPi / inAzimuthSteps;

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

		number elevation = Math::Arcos(outgoingDirection.Dot(n));
		size_t index = (size_t)Math::Floor(elevation / outElevationStep);

		std::vector<number>::iterator match = std::lower_bound(angleCdfs[index]->Cdf.begin(), angleCdfs[index]->Cdf.end(), v);
		size_t matchIndex = match - angleCdfs[index]->Cdf.begin();

		size_t elevationIndex = matchIndex / inAzimuthSteps;
		size_t azimuthIndex = matchIndex % inAzimuthSteps;

		number inElevation = num(elevationIndex + sample[0]) * inElevationStep;
		number inAzimuth = num(azimuthIndex + sample[1]) * inAzimuthStep;

		pdf = angleCdfs[index]->Values[matchIndex];

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

		number hf = (inAzimuthSteps*inElevationSteps)/Consts::TwoPi;

		std::cout << "Precomputing importance sampling for " << material->GetName() << std::endl;
		for(size_t i = 0; i < outElevationSteps; i++)
		{
			std::cout << (int)(100*(i+1)/num(outElevationSteps)) << "%  \r";
			number cdf = 0;

			number outElevation = num(i + 0.5) * outElevationStep;
			intersection.RayDirection.Set(-Math::Sin(outElevation), 0, -Math::Cos(outElevation));

			shared_ptr<AnglePrecalc> precalc(new AnglePrecalc);
			for(size_t j = 0; j < inElevationSteps; j++)
			{
				number inElevation = num(j + 0.5) * inElevationStep;
				number inElevationCos = Math::Cos(inElevation);
				number inElevationSin = Math::Sin(inElevation);

				for(size_t k = 0; k < inAzimuthSteps; k++)
				{
					number inAzimuth = (k + 0.5) * inAzimuthStep;
					number inAzimuthCos = Math::Cos(inAzimuth);
					number inAzimuthSin = Math::Sin(inAzimuth);

					RayLight incomingRay;
					incomingRay.Direction.Set( -inElevationSin * inAzimuthCos,
						-inElevationSin * inAzimuthSin,
						-inElevationCos);
					incomingRay.Radiance.SetOne();

					number v = (material->CalculateBsdf(incomingRay, intersection) 
						* Math::Abs(incomingRay.Direction.Z)).GetAverage();
					cdf += v;

					precalc->Values.push_back(v);
					precalc->Cdf.push_back(cdf);
				}
			}

			if (cdf == 0)
			{
				number spread = inAzimuthSteps*inElevationSteps;
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
			size_t tableSize = inAzimuthSteps*inElevationSteps;

			std::cout << "Loading importance sampling for " << materialSignature << "... ";

			for(size_t i = 0; i<outElevationSteps; i++)
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

				angleCdfs.push_back(precalc);
			}

			std::cout << "done" << std::endl;
			return true;
		}
		catch(...)
		{
			std::cout << "failed" << std::endl;
			return false;
		}
	}

	void PrecomputedImportanceSampler::SaveToFile(const std::string& materialSignature)
	{
		std::string fileName = SignatureToFilename(materialSignature, ".brdf");

		std::ofstream outFile(fileName.c_str(), std::ofstream::binary);
		size_t tableSize = inAzimuthSteps*inElevationSteps;

		for(size_t i = 0; i<outElevationSteps; i++)
		{
			shared_ptr<AnglePrecalc> precalc = angleCdfs[i];
			outFile.write(reinterpret_cast<char*>(&precalc->Values[0]), tableSize*sizeof(number));
			outFile.write(reinterpret_cast<char*>(&precalc->Cdf[0]), tableSize*sizeof(number));
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

		int inElevationIndex = (int)(inElevation / inElevationStep);
		int inAzimuthIndex = (int)(inAzimuth / inAzimuthStep);
		int outElevationIndex = (int)(outElevation / outElevationStep);

		return angleCdfs[Math::Min(outElevationSteps-1, outElevationIndex)]->Values[inElevationIndex*inAzimuthSteps + inAzimuthIndex];
	}
}
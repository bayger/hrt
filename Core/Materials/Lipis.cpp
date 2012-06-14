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
#include "StdAfx.h"
#include "Lipis.h"
#include "..\Serialization\LipisSerializer.h"

namespace Hrt
{
  const size_t ELEVATION_COUNT = 90*3;
  const size_t AZIMUTH_COUNT = 360;
  const number ELEVATION_STEP = Consts::HalfPi / ELEVATION_COUNT;
  const number AZIMUTH_STEP = Consts::TwoPi / AZIMUTH_COUNT;
  // this is an additional normalization factor for PDF (hemisphere chunk)
  const number hf = (AZIMUTH_COUNT*ELEVATION_COUNT)/Consts::TwoPi;

  //
  // NON-MEMBER FUNCTIONS
  //

  /// Computes BRDF values for all nodes on the hemisphere for given intersection data (outgoing vector)
  static void ComputeBrdfForNodes(MaterialPtr material, std::vector<number>& values, Intersection& intersection)
  {
    values.clear();

    for(size_t ie = 0; ie <= ELEVATION_COUNT; ie++)
    {
      // incoming elevation angle is cos^-1(0->1) due to the need of constant density
      number inElevation = Math::Arcos(num(ie) / ELEVATION_COUNT);
      number inElevationCos = Math::Cos(inElevation);
      number inElevationSin = Math::Sin(inElevation);

      for(size_t az = 0; az <= AZIMUTH_COUNT; az++)
      {
        // azimuth angle is spread uniformly
        number inAzimuth = az * AZIMUTH_STEP;
        number inAzimuthCos = Math::Cos(inAzimuth);
        number inAzimuthSin = Math::Sin(inAzimuth);

        RayLight incomingRay;
        incomingRay.Direction.Set( -inElevationSin * inAzimuthCos,
          -inElevationSin * inAzimuthSin,
          -inElevationCos);
        incomingRay.Radiance.SetOne();

        // BRDF computation goes here
        LightingType::Enum lightingType = LightingType::AllReflection;
        number v = (material->CalculateBsdf(incomingRay, intersection, lightingType) 
          * Math::Abs(incomingRay.Direction.Z)).GetAverage();

        // NOTE: for now we are ignoring NaNs and put zeros instead
        values.push_back(Math::IsNan(v) ? 0 : v);
      }
    }
  }

  /// Calculates average values of BRDF for each fields on the hemisphere
  static void ComputeBrdfForFields(std::vector<number>& values, std::vector<number>& fieldValues) 
  {
    fieldValues.clear();
    for(size_t ie = 0; ie < ELEVATION_COUNT; ie++)
    {
      for(size_t az = 0; az < AZIMUTH_COUNT; az++)
      {
        number v = (values[ie*(AZIMUTH_COUNT+1) + az]
                  +values[ie*(AZIMUTH_COUNT+1) + az + 1]
                  +values[(ie+1)*(AZIMUTH_COUNT+1) + az]
                  +values[(ie+1)*(AZIMUTH_COUNT+1) + az + 1]) / 4;
        fieldValues.push_back(v);
      }
    }
  }

  /// This one computes unnormalized CDF values and returns the cumulated BRDF sum (for the hemisphere)
  static number ComputeCdfForFields(std::vector<number>& fieldValues, std::vector<number>& fieldCdfs) 
  {
    fieldCdfs.clear();
    number cdf = 0;
    for(size_t ie = 0; ie < ELEVATION_COUNT; ie++)
    {
      for(size_t az = 0; az < AZIMUTH_COUNT; az++)
      {
        cdf += fieldValues[ie*AZIMUTH_COUNT + az];
        fieldCdfs.push_back(cdf);
      }
    }

    return cdf;
  }

  /// Normalizes PDF and CDF tables using cumulated BRDF sum for whole hemisphere
  static void NormalizeTables(std::vector<number>& values, std::vector<number>& fieldCdfs, number cumulatedValue)
  {
    for(std::vector<number>::iterator it = fieldCdfs.begin(); it != fieldCdfs.end(); it++)
      *it /= cumulatedValue;

    for(std::vector<number>::iterator it = values.begin(); it != values.end(); it++)
      *it /= cumulatedValue/hf;
  }

  /// This function does linear interpolation of PDF for given PDF table and incoming angles
  static number CalculatePdf(std::vector<number>& values, number inElevation, number inAzimuth)
  {
    number e = Math::Cos(inElevation) * ELEVATION_COUNT;
    size_t el = (size_t)Math::Floor(e);
    size_t eh = (size_t)Math::Ceiling(e);
    number de = e - el;
    number a = inAzimuth / AZIMUTH_STEP;
    size_t al = (size_t)Math::Floor(a);
    size_t ah = (size_t)Math::Ceiling(a);
    number da = a - al;

    number pdfElAl = values[el*(AZIMUTH_COUNT+1) + al];
    number pdfElAh = values[el*(AZIMUTH_COUNT+1) + ah];
    number pdfEhAl = values[eh*(AZIMUTH_COUNT+1) + al];
    number pdfEhAh = values[eh*(AZIMUTH_COUNT+1) + ah];

    number vl = pdfElAl * (1 - da) + pdfElAh * da;
    number vh = pdfEhAl * (1 - da) + pdfEhAh * da;

    return vl * (1 - de) + vh * de;
  }

  /// Computes ideal reflection (glossy, duffuse + specular)
  static number ComputeIdealReflection(MaterialPtr material, Intersection& intersection)
  {
    RayLight incomingRay;
    incomingRay.Direction = intersection.RayDirection.Reflect(intersection.Normal);
    incomingRay.Radiance.SetOne();

    // BRDF computation goes here
    LightingType::Enum lightingType = static_cast<LightingType::Enum>(LightingType::AllReflection | LightingType::IdealSpecular);
    number v = (material->CalculateBsdf(incomingRay, intersection, lightingType) 
      * Math::Abs(incomingRay.Direction.Z)).GetAverage();

    return v;
  }

  //
  // CLASS MEMBERS
  //

  Lipis::Lipis(void)
    : isPrecomputed(false)
  {
  }

  void Lipis::Precompute(MaterialPtr material)
  {
    if (isPrecomputed)
      return;
    if (LipisSerializer::Load(material->GetSignature(), ELEVATION_COUNT, AZIMUTH_COUNT, angleData))
    {
      isPrecomputed = true;
      return;
    }

    std::cout << "Precomputing importance sampling for " << material->GetSignature() << std::endl;

    Intersection intersection;
    intersection.Normal = Vector3D::UnitZ;
    intersection.TangentU = Vector3D::UnitX;
    intersection.TangentV = Vector3D::UnitY;
    std::vector<number> values;
    values.reserve((AZIMUTH_COUNT+1)*(ELEVATION_COUNT+1));
    std::vector<number> fieldValues;
    fieldValues.reserve(AZIMUTH_COUNT*ELEVATION_COUNT);
    std::vector<number> fieldCdfs;
    fieldCdfs.reserve(AZIMUTH_COUNT*ELEVATION_COUNT);

    for(size_t oe = 0; oe <= ELEVATION_COUNT; oe++)
    {
      // outgoing elevation angle is spread uniformly
      number outElevation = (oe) * ELEVATION_STEP;
      intersection.RayDirection.Set(-Math::Sin(outElevation), 0, -Math::Cos(outElevation));

      std::cout << std::setprecision(3) << (number)oe*100/ELEVATION_COUNT << "%" << std::endl;

      number idealReflection = ComputeIdealReflection(material, intersection);
      ComputeBrdfForNodes(material, values, intersection);
      ComputeBrdfForFields(values, fieldValues);
      number cumulatedValue = ComputeCdfForFields(fieldValues, fieldCdfs);
      NormalizeTables(values, fieldCdfs, cumulatedValue);

      shared_ptr<LipisAngleData> data(new LipisAngleData);
      data->OutgoingAngle = outElevation;
      data->IdealReflectionCdf = idealReflection / cumulatedValue;
      data->IdealReflectionPdf = idealReflection / (cumulatedValue/hf);
      data->PdfValues.resize(values.size());
      std::copy(values.begin(), values.end(), data->PdfValues.begin());
      data->CdfValues.resize(fieldCdfs.size());
      std::copy(fieldCdfs.begin(), fieldCdfs.end(), data->CdfValues.begin());
      angleData.push_back(data);
    }

    isPrecomputed = true;
    LipisSerializer::Save(material->GetSignature(), ELEVATION_COUNT, AZIMUTH_COUNT, angleData);
  }

  Hrt::Vector3D Lipis::SampleVector(number* sample, 
    const Vector3D& outgoingDirection, 
    const Vector3D& tangentU, 
    const Vector3D& tangentV, 
    const Vector3D& n, 
    number& pdf, 
    LightingType::Enum& lightingType)
  {
    lightingType = LightingType::AllReflection;

    // NOTE: this is actually much better than: m_random.RandomEndOpen(0, 1) for non-RandomSampler level samplers of course
    number v = (sample[0]+sample[1])/2;

    number stepIndex = Math::Arcos(outgoingDirection.Dot(n)) / ELEVATION_STEP;
    size_t indexLo = (size_t)Math::Floor(stepIndex);
    size_t indexHi = (size_t)Math::Ceiling(stepIndex);

    number loPart = indexHi - stepIndex;
    number hiPart = stepIndex - indexLo;
    if (loPart == 0 && hiPart == 0) 
      loPart = 1;

    bool useLo = (v < loPart);
    number inAzimuth, inElevation;

    // first check for ideal reflection case
    if (useLo)
    {
      GetReflectionForIndex(v, indexLo, lightingType, inElevation, inAzimuth, pdf, outgoingDirection, n, sample);
    }
    else
    {
      GetReflectionForIndex(v, indexHi, lightingType, inElevation, inAzimuth, pdf, outgoingDirection, n, sample);
    }

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

  Hrt::number Lipis::GetPdf(const Vector3D& incomingDirection, const Vector3D& outgoingDirection, const Vector3D& tangentU, const Vector3D& tangentV, const Vector3D& n, const LightingType::Enum lightingType)
  {
    number outElevation = Math::Arcos(outgoingDirection.Dot(n));
    size_t outElevationIndex = (size_t)Math::Floor(outElevation / ELEVATION_STEP);

    // first check for ideal reflection case
    //if (lightingType == static_cast<LightingType::Enum>(LightingType::AllReflection | LightingType::IdealSpecular))
    //  return angleData[outElevationIndex]->IdealReflectionPdf;

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

    number inElevation = Math::Arcos(z);
    number inAzimuth = Math::Atan(x, y);

    if (inAzimuth < 0)
      inAzimuth += Consts::TwoPi;

    return CalculatePdf(angleData[outElevationIndex]->PdfValues, inElevation, inAzimuth);
  }

  void Lipis::GetReflectionForIndex(number v, 
    size_t index, 
    LightingType::Enum& lightingType, 
    number& inElevation,
    number& inAzimuth,
    number &pdf, 
    const Vector3D &outgoingDirection, 
    const Vector3D& n, 
    number* sample)
  {
    std::vector<number>::iterator match = std::lower_bound(angleData[index]->CdfValues.begin(), 
      angleData[index]->CdfValues.end(), 
      v);
    size_t matchIndex = match - angleData[index]->CdfValues.begin();
    size_t elevationIndex = matchIndex / (AZIMUTH_COUNT);
    size_t azimuthIndex = matchIndex % (AZIMUTH_COUNT);
    inElevation = Math::Arcos(num(elevationIndex + sample[0]) / ELEVATION_COUNT);
    inAzimuth = num(azimuthIndex + sample[1]) * AZIMUTH_STEP;
    pdf = CalculatePdf(angleData[index]->PdfValues, inElevation, inAzimuth);
  }

}
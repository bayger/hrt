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

namespace Hrt
{
  const size_t ELEVATION_COUNT = 180;
  const size_t AZIMUTH_COUNT = 180;
  const number ELEVATION_STEP = Consts::HalfPi / ELEVATION_COUNT;
  const number AZIMUTH_STEP = Consts::Pi / AZIMUTH_COUNT;

  Lipis::Lipis(void)
  {
  }

  static void ComputeBrdfForNodes(MaterialPtr material, std::vector<number>& values, Intersection& intersection)
  {
    values.clear();

    for(size_t ie = 0; ie <= ELEVATION_COUNT; ie++)
    {
      // incoming elevation angle is cos^-1(0->1) due to the need of constant density
      number inElevation = Math::Arcos(ie / ELEVATION_COUNT);
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

  static void NormalizeTables(std::vector<number>& values, std::vector<number>& fieldCdfs, number cumulatedValue)
  {
    // make values PDF normalized
    for(size_t ie = 0; ie <= ELEVATION_COUNT; ie++)
    {
      for(size_t az = 0; az <= AZIMUTH_COUNT; az++)
      {
        values[ie*(AZIMUTH_COUNT+1) + az] /= cumulatedValue;
      }
    }

    // normalize CDFs (all must sum to 1)
    for(size_t ie = 0; ie < ELEVATION_COUNT; ie++)
    {
      for(size_t az = 0; az < AZIMUTH_COUNT; az++)
      {
        fieldCdfs[ie*AZIMUTH_COUNT + az] /= cumulatedValue;
      }
    }
  }

  static number CalculatePdf(std::vector<number>& values, number inElevation, number inAzimuth)
  {
    number e = inElevation / ELEVATION_STEP;
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

  void Lipis::Precompute(MaterialPtr material)
  {
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

    for(size_t oe = 0; oe < ELEVATION_COUNT; oe++)
    {
      // outgoing elevation angle is spread uniformly
      number outElevation = oe * ELEVATION_STEP;
      intersection.RayDirection.Set(-Math::Sin(outElevation), 0, -Math::Cos(outElevation));

      ComputeBrdfForNodes(material, values, intersection);
      ComputeBrdfForFields(values, fieldValues);
      number cumulatedValue = ComputeCdfForFields(fieldValues, fieldCdfs);
      NormalizeTables(values, fieldCdfs, cumulatedValue);

      shared_ptr<LipisAngleData> data(new LipisAngleData);
      data->OutgoingAngle = outElevation;
      std::copy(values.begin(), values.end(), data->PdfValues.begin());
      std::copy(fieldCdfs.begin(), fieldCdfs.end(), data->CdfValues.begin());
      angleData.push_back(data);
    }
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

    size_t index = (size_t)Math::Floor(Math::Arcos(outgoingDirection.Dot(n)) / ELEVATION_STEP);

    std::vector<number>::iterator match = std::lower_bound(angleData[index]->CdfValues.begin(), 
      angleData[index]->CdfValues.end(), 
      v);
    size_t matchIndex = match - angleData[index]->CdfValues.begin();

    size_t elevationIndex = matchIndex / AZIMUTH_COUNT;
    size_t azimuthIndex = matchIndex % AZIMUTH_COUNT;

    number inElevation = Math::Arcos(num(elevationIndex + sample[0]) / ELEVATION_COUNT);
    number inAzimuth = num(azimuthIndex + sample[1]) * AZIMUTH_COUNT;
    pdf = CalculatePdf(angleData[index]->PdfValues, inElevation, inAzimuth);

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

    size_t outElevationIndex = (size_t)Math::Floor(outElevation / ELEVATION_STEP);

    return CalculatePdf(angleData[outElevationIndex]->PdfValues, inElevation, inAzimuth);
  }

}
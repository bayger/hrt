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
        values.push_back(v);
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
    }
  }
}
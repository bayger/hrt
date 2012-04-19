/*
H-RT Core - the core of the H-RayTracer ray tracing renderer.
Copyright (c) 2006-2010 H-RT Team.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/
#include "stdafx.h"
#include "Material.h"
#include "SamplingHelper.h"

namespace Hrt
{

  Spectrum Material::CalculateBsdf(const RayLight& incomingRay,
    const Intersection& intersection)
  {
    return CalculateBsdf(incomingRay, intersection, 
      LightingType::AllReflection);
  }

  Hrt::Spectrum Material::CalculateBsdfIdealSpecular( const RayLight& incomingRay, 
    const Intersection& intersection )
  {
    return CalculateBsdf(incomingRay, intersection,
      (LightingType::Enum)(LightingType::AllReflection + 
      LightingType::IdealSpecular));
  }

  void Material::CalculateReflectedRay( const RayLight& incomingRay, 
    const Intersection& intersection, RayLight& reflectedRay, bool isInSpecularCone )
  {
    reflectedRay.Radiance = CalculateBsdf(incomingRay, intersection, 
      (LightingType::Enum)(LightingType::AllReflection 
      + (isInSpecularCone 
      ? LightingType::IdealSpecular 
      : LightingType::Nothing))
      );

    reflectedRay.MediumRefractionRe = incomingRay.MediumRefractionRe;
    reflectedRay.MediumRefractionIm = incomingRay.MediumRefractionIm;
    reflectedRay.Direction = -intersection.RayDirection;
    reflectedRay.Position = intersection.Position;
    reflectedRay.LightNormal = reflectedRay.Direction;
    reflectedRay.TotalDistance = intersection.DistanceFromRayOrigin;

    // ignore polarization by just copying data from incomingRay
    for(unsigned i=0; i<Spectrum::LambdaCount; i++)
      reflectedRay.Polarization[i] = incomingRay.Polarization[i];
    reflectedRay.PolarizationVector = incomingRay.PolarizationVector;
  }

  Vector3D Material::SampleVector(number* sample, const Vector3D& outgoingDirection, const Vector3D& tangentU, 
    const Vector3D& tangentV, const Vector3D& n, number& pdf)
  {
    // by default it samples over cosine lobe
    //return SamplingHelper::SampleHemisphere(sample, tangentU, tangentV, n, pdf);
    return SamplingHelper::SampleHemisphereCosineLobe(sample, tangentU, tangentV, n, pdf);
  }

  Hrt::number Material::CalculatePdf(const Vector3D& outgoingDirection, const Vector3D& tangentU, const Vector3D& tangentV, 
    const Vector3D& n, const Vector3D& incomingDirection)
  {
    return SamplingHelper::GetPdfHemisphereCosineLobe(n, -incomingDirection);
  }
}

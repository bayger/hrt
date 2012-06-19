/*
H-RT Core - the core of the H-RayTracer ray tracing renderer.
Copyright (c) Patryk Bajer, H-RT.

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
#include "Lambertian.h"
#include "..\Serialization\SerializationHelper.h"
#include "Lipis.h"
#include "..\SamplingHelper.h"

namespace Hrt
{
  Lambertian::Lambertian()
    : m_reflectance(Spectrum(1))
  {
  }

  static std::string yamlType("lambertian");
  const std::string& Lambertian::YamlType()
  {
    return yamlType;
  }

  const std::string Lambertian::GetSignature()
  {
    return str(format("r=%1%") % m_reflectance.ToString());
  }

  bool Lambertian::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
  {
    std::string scalarValue = parser.CurrentValue();
    if (scalarValue == "reflectance")
      m_reflectance = SerializationHelper::ReadSpectrum(parser);
    else
      return Material::ProcessYamlScalar(parser, context);

    return true;
  }

  Hrt::Spectrum Lambertian::CalculateBrdf(const RayLight& incomingRay, const Intersection& intersection, LightingType::Enum lightingType)
  {
    Vector3D k2 = -intersection.RayDirection;
    number nk2 = intersection.Normal.Dot(k2);

    return m_reflectance / Consts::Pi * incomingRay.Radiance * nk2;
  }  
}
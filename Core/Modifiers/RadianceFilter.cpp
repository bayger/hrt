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
#include "RadianceFilter.h"
#include "..\Serialization\SerializationHelper.h"

namespace Hrt
{
  RadianceFilter::RadianceFilter()
    : m_filteringFactor(1)
  {}
  
  Hrt::Spectrum RadianceFilter::Modify(const Spectrum& originalSpectrum, 
    const RayLight& incomingRay, 
    const Intersection& intersection)
  {
    return originalSpectrum * m_filteringFactor;
  }

  bool RadianceFilter::ProcessYamlScalar(YamlParser& parser, SerializationContext& context)
  {
    std::string scalarValue = parser.CurrentValue();
    if (scalarValue == "pass-through")
      SetFilteringFactor(SerializationHelper::ReadSpectrum(parser));
    else
      return false;

    return true;
  }

  static std::string yamlType("checkerboard");
  const std::string& RadianceFilter::YamlType()
  {
    return yamlType;
  }

}
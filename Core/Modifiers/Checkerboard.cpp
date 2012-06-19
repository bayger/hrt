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
#include "Checkerboard.h"
#include "..\Serialization\SerializationHelper.h"

namespace Hrt
{

  Checkerboard::Checkerboard()
    : m_scaleX(1),
    m_scaleY(1),
    m_scaleZ(1),
    m_whiteAbsorption(1),
    m_blackAbsorption(0)
  {
  }

  Spectrum Checkerboard::Modify(const Spectrum& originalSpectrum, 
    const RayLight& incomingRay, 
    const Intersection& intersection) 
  {
    int tx = (int)Math::Ceiling(m_scaleX * intersection.Position.X + 0.5) & 1;
    int ty = (int)Math::Ceiling(m_scaleY * intersection.Position.Y + 0.5) & 1;
    int tz = (int)Math::Ceiling(m_scaleZ * intersection.Position.Z + 0.5) & 1;

    return ((tx+ty+tz) & 1) == 1 ? originalSpectrum*m_whiteAbsorption : originalSpectrum*m_blackAbsorption;
  }

  bool Checkerboard::ProcessYamlScalar(YamlParser& parser, SerializationContext& context)
  {
    std::string scalarValue = parser.CurrentValue();
    if (scalarValue == "scale-x")
      parser.ReadScalar(m_scaleX);
    else if (scalarValue == "scale-y")
      parser.ReadScalar(m_scaleY);
    else if (scalarValue == "scale-z")
      parser.ReadScalar(m_scaleZ);
    else if (scalarValue == "white-absorption")
      m_whiteAbsorption = SerializationHelper::ReadSpectrum(parser);
    else if (scalarValue == "black-absorption")
      m_blackAbsorption = SerializationHelper::ReadSpectrum(parser);
    else
      return false;

    return true;
  }

  static std::string yamlType("checkerboard");
  const std::string& Checkerboard::YamlType()
  {
    return yamlType;
  }
}
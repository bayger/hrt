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
#pragma once
#include "OutgoingRadianceModifier.h"

namespace Hrt
{
  class Checkerboard
    : public OutgoingRadianceModifier
  {
  public:
    Checkerboard();

    virtual Spectrum Modify(const Spectrum& originalSpectrum, 
      const RayLight& incomingRay, 
      const Intersection& intersection);

    AUTO_PROPERTY(number, m_scaleX, ScaleX);

    AUTO_PROPERTY(number, m_scaleY, ScaleY);

    AUTO_PROPERTY(number, m_scaleZ, ScaleZ);

    AUTO_GETTER(Spectrum, m_whiteAbsorption, WhiteAbsorption);

    void SetWhiteAbsorption(const Spectrum& val)
    {
      m_whiteAbsorption = val;
      m_whiteAbsorption.Clamp(0, 1);
    }

    AUTO_GETTER(Spectrum, m_blackAbsorption, BlackAbsorption);

    void SetBlackAbsorption(const Spectrum& val)
    {
      m_blackAbsorption = val;
      m_blackAbsorption.Clamp(0, 1);
    }

    virtual bool ProcessYamlScalar(YamlParser& parser, 
      SerializationContext& context);

    virtual const std::string& YamlType();

  private:
    number m_scaleX;
    number m_scaleY;
    number m_scaleZ;
    Spectrum m_whiteAbsorption;
    Spectrum m_blackAbsorption;
  };
}
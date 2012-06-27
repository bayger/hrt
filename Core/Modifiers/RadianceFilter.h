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

  class RadianceFilter
    : public OutgoingRadianceModifier
  {
  public:
    RadianceFilter();

    virtual Spectrum Modify(const Spectrum& originalSpectrum, 
      const RayLight& incomingRay, 
      const Intersection& intersection);

    AUTO_GETTER(Spectrum, m_filteringFactor, FilteringFactor);

    void SetFilteringFactor(const Spectrum& val)
    {
      m_filteringFactor = val;
      m_filteringFactor.Clamp(0, 1);
    }

  private:
    Spectrum m_filteringFactor;
  };
}
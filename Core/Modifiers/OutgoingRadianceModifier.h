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
#include "..\Serialization\IYamlSerializable.h"
#include "..\Spectrum.h"
#include "..\RayLight.h"
#include "..\Intersection.h"

namespace Hrt
{
  /// Base class for outgoing radiance modifiers
  class OutgoingRadianceModifier
    : public IYamlSerializable
  {
  public:
    virtual Spectrum Modify(const Spectrum& originalSpectrum, 
      const RayLight& incomingRay,
      const Intersection& intersection)=0;
  };

  typedef shared_ptr<OutgoingRadianceModifier> OutgoingRadianceModifierOwnedPtr;

  typedef const shared_ptr<OutgoingRadianceModifier>& OutgoingRadianceModifierPtr;
}
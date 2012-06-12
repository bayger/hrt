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
#include "../Common.h"
#include "../Material.h"
#include "ImportanceSampler.h"

namespace Hrt
{

  class Lambertian
    : public Material, 
    public enable_shared_from_this<Lambertian>
  {
  public:
    Lambertian();

    virtual Spectrum CalculateBsdf(const RayLight& incomingRay, 
      const Intersection& intersection, LightingType::Enum lightingType);

    virtual void Initialize() { /* nothing to do */}

    // Diffuse reflectance spectrum.
    Hrt::Spectrum GetReflectance() const { return m_reflectance; }
    void SetReflectance(Hrt::Spectrum& val) { m_reflectance = val; }

    virtual const std::string GetSignature();

    // IYamlSerializable Implementation
    virtual bool ProcessYamlScalar(YamlParser& parser, SerializationContext& context);
    virtual const std::string& YamlType();

  private:
    Spectrum m_reflectance;
  };

}
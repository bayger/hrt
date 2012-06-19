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
#include "Material.h"
#include "SamplingHelper.h"
#include "Materials\Lipis.h"
#include "Materials\PrecomputedImportanceSampler.h"

namespace Hrt
{

  Material::Material() 
    : m_refractionRe(1), 
    m_transparency(0), 
    m_importanceSamplingType(ImportanceSamplingType::CosineLobe)
  {
  }

  Vector3D Material::SampleVector(number* sample, const Vector3D& outgoingDirection, const Vector3D& tangentU, 
    const Vector3D& tangentV, const Vector3D& n, number& pdf, LightingType::Enum& lightingType)
  {
    switch(m_importanceSamplingType)
    {
    case ImportanceSamplingType::CosineLobe:
      return SamplingHelper::SampleHemisphereCosineLobe(sample, tangentU, tangentV, n, pdf);
    case ImportanceSamplingType::Uniform:
      return SamplingHelper::SampleHemisphere(sample, tangentU, tangentV, n, pdf);
    default:
      return m_importanceSampler->SampleVector(sample, outgoingDirection, tangentU, tangentV, n, pdf, lightingType);
    }
  }

  Hrt::number Material::CalculatePdf(const Vector3D& outgoingDirection, const Vector3D& tangentU, const Vector3D& tangentV, 
    const Vector3D& n, const Vector3D& incomingDirection, const LightingType::Enum lightingType)
  {
    switch(m_importanceSamplingType)
    {
    case ImportanceSamplingType::CosineLobe:
      return SamplingHelper::GetPdfHemisphereCosineLobe(n, -incomingDirection);
    case ImportanceSamplingType::Uniform:
      return SamplingHelper::GetPdfHemisphere(n, -incomingDirection);
    default:
      return m_importanceSampler->GetPdf(incomingDirection, outgoingDirection, tangentU, tangentV, n, lightingType);
    }
  }

  bool Material::ProcessYamlScalar(YamlParser& parser, SerializationContext& context)
  {
    std::string scalarValue = parser.CurrentValue();

    if (scalarValue == "importance-sampling")
    {
      std::string isMode;
      parser.ReadScalar(isMode);
      if (isMode == "cosine-lobe")
        m_importanceSamplingType = ImportanceSamplingType::CosineLobe;
      else if (isMode == "uniform")
        m_importanceSamplingType = ImportanceSamplingType::Uniform;
      else if (isMode == "lipis")
        m_importanceSamplingType = ImportanceSamplingType::Lipis;
      else if (isMode == "spis")
        m_importanceSamplingType = ImportanceSamplingType::Spis;
    }
    else
      return NamedObject::ProcessYamlScalar(parser, context);

    return true;
  }

  void Material::Initialize()
  {
    switch (m_importanceSamplingType)
    {
    case ImportanceSamplingType::Lipis:
      m_importanceSampler.reset(new Lipis());
      m_importanceSampler->Precompute(shared_from_this());
      break;
    case ImportanceSamplingType::Spis:
      m_importanceSampler.reset(new PrecomputedImportanceSampler());
      m_importanceSampler->Precompute(shared_from_this());
      break;
    default:
      m_importanceSampler.reset();
      break;
    }
  }

}

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
#include "AreaLight.h"
#include "../Sampler.h"
#include "../RayLight.h"
#include "../Vector3D.h"
#include "../Matrix.h"

namespace Hrt
{
	AreaLight::AreaLight(LightEmitterPtr emitter)
	{
		SetEmitter(emitter);
	}

	void AreaLight::Prepare(const Vector3D& target, const Vector3D& normal, RenderingContext& rc)
	{
		if (m_emitter == NULL)
			throw new InvalidOperationException("No light emitter provided!");

		m_targetPosition = target;
		m_targetNormal = normal;
		m_emitter->PrepareEmitter(target, normal, rc);
	}

	bool AreaLight::GenerateRayLight(RayLight* ray, number& pdf, RenderingContext& rc)
	{
		return m_emitter->GenerateRayLight(ray, pdf, rc);
	}

	bool AreaLight::ProcessYamlScalar(YamlParser& parser, SerializationContext& context)
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "emitter-shape")
			parser.ReadScalar(m_emitterName);

		return true;
	}

	static std::string yamlType("point-light");
	const std::string& AreaLight::YamlType()
	{
		return yamlType;
	}

	void AreaLight::SetEmitter(LightEmitterPtr emitter)
	{
		m_emitter = emitter;
		m_emitterShape = dynamic_pointer_cast<Shape>(emitter);
	}

	void AreaLight::PrepareForConcurrency(size_t numberOfThreads)
	{
		ISupportsConcurrency::PrepareForConcurrency(numberOfThreads);
		m_emitter->PrepareForConcurrency(numberOfThreads);
	}

  shared_ptr<Light> AreaLight::Clone()
  {
    return LightOwnedPtr(new AreaLight(*this));
  }

}

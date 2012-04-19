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

#include "PointLight.h"
#include "../RayLight.h"
#include "../Serialization/SerializationHelper.h"

namespace Hrt
{
	PointLight::PointLight()
		: m_prepared(false)
	{
	}

	PointLight::PointLight(const Vector3D& position, const Spectrum& power)
		: m_position(position)
	{
		SetPower(power);
	}

	bool PointLight::GenerateRayLight(RayLight* ray, number& pdf, RenderingContext& rc)
	{
		if (!m_prepared)
			return false;

		ray->Direction = (m_target-m_position).Normalize();
		ray->LightNormal = ray->Direction;
		ray->Position = m_position;
		ray->Radiance = m_intensity / (m_target-m_position).LengthSquared();
		pdf = 1;

		m_prepared = false;
		return true;
	}

	bool PointLight::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "position")
			m_position = SerializationHelper::ReadVector3D(parser);
		else if (scalarValue == "power")
			SetPower(SerializationHelper::ReadSpectrum(parser));
		else
			return NamedObject::ProcessYamlScalar(parser, context);

		return true;
	}

	static std::string yamlType("point-light");
	const std::string& PointLight::YamlType()
	{
		return yamlType;
	}

  shared_ptr<Light> PointLight::Clone()
  {
    return LightOwnedPtr(new PointLight(*this));
  }

}

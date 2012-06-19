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
#include "Phong.h"

namespace Hrt
{

	Phong::Phong()
		: m_powerSpecular(10),
		m_specular(num(0.5)),
		m_diffuse(num(0.5))
	{
    m_importanceSamplingType = ImportanceSamplingType::Lipis;
	}

	Hrt::Spectrum Phong::CalculateBrdf( const RayLight& incomingRay, 
		const Intersection& intersection, LightingType::Enum lightingType )
	{
		Vector3D h = (-(incomingRay.Direction + intersection.RayDirection)).Normalize();
		number cos_nh = intersection.Normal.Dot(h);

		Spectrum result = (m_specular * Math::Pow(cos_nh, m_powerSpecular) + m_diffuse) 
			* incomingRay.Radiance;

		return result;
	}

	bool Phong::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "specular-power")
			parser.ReadScalar(m_powerSpecular);
		else if (scalarValue == "specular-absorption")
			m_specular = SerializationHelper::ReadSpectrum(parser);
		else if (scalarValue == "diffuse-absorption")
			m_diffuse = SerializationHelper::ReadSpectrum(parser);
		else
			return NamedObject::ProcessYamlScalar(parser, context);

		return true;

	}

	static std::string yamlType("phong");
	const std::string& Phong::YamlType()
	{
		return yamlType;
	}

	const std::string Phong::GetSignature()
	{
		return str(format("%1%:sp=%2%,d=%3%,s=%4%") % yamlType % m_powerSpecular % m_diffuse.ToString() % m_specular.ToString());
	}
}

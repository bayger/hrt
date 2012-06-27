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
#include "Mirror.h"
#include "..\Serialization\SerializationHelper.h"

namespace Hrt
{

	Mirror::Mirror()
		: m_absorption(1)
	{
	}

	Hrt::Spectrum Mirror::CalculateBrdf(const RayLight& incomingRay, const Intersection& intersection, LightingType::Enum lightingType)
	{
		if ((lightingType & LightingType::SpecularOnly) == 0)
			return Spectrum::Zero;

		Vector3D r = incomingRay.Direction.Reflect(-intersection.Normal);
		if (!intersection.RayDirection.AlmostEqualTo(r))
			return Spectrum::Zero;

		return incomingRay.Radiance * m_absorption / intersection.Normal.Dot(-intersection.RayDirection);
	}

	Hrt::Vector3D Mirror::SampleVector(number* sample, const Vector3D& outgoingDirection, const Vector3D& tangentU, const Vector3D& tangentV, 
		const Vector3D& n, number& pdf, LightingType::Enum& lightingType)
	{
		pdf = 1;
    lightingType = LightingType::IdealSpecular;
		return outgoingDirection.Reflect(n);
	}

	Hrt::number Mirror::CalculatePdf(const Vector3D& outgoingDirection, const Vector3D& tangentU, const Vector3D& tangentV, const Vector3D& n, 
		const Vector3D& incomingDirection, const LightingType::Enum lightingType)
	{
		return !incomingDirection.AlmostEqualTo(outgoingDirection.Reflect(n)) && lightingType == LightingType::IdealSpecular ? 0 : 1;
	}

	static std::string yamlType("mirror");

	const std::string Mirror::GetSignature()
	{
		return str(format("%1%:%2%") % yamlType % m_absorption.ToString());
	}
	
	const std::string& Mirror::YamlType()
	{
		return yamlType;
	}

	bool Mirror::ProcessYamlScalar(YamlParser& parser, SerializationContext& context)
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "absorption")
			m_absorption = SerializationHelper::ReadSpectrum(parser);
		else
			return Material::ProcessYamlScalar(parser, context);

		return true;
	}
}
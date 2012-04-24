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

namespace Hrt
{

	class Mirror : public Material
	{
	public:
		Mirror();

		// Material overrides

		virtual Spectrum CalculateBsdf(const RayLight& incomingRay, 
			const Intersection& intersection, 
			LightingType::Enum lightingType);

		virtual Vector3D SampleVector(number* sample, const Vector3D& outgoingDirection, 
			const Vector3D& tangentU, const Vector3D& tangentV, const Vector3D& n, number& pdf);

		virtual number CalculatePdf(const Vector3D& outgoingDirection, const Vector3D& tangentU, const Vector3D& tangentV, 
			const Vector3D& n, const Vector3D& incomingDirection);

		virtual const std::string GetSignature();

		// Properties

		Hrt::Spectrum GetDiffuse() const { return m_absorption; }
		void SetDiffuse(const Hrt::Spectrum& val) { m_absorption = val; }

		// IYamlSerializable overrides

		virtual bool ProcessYamlScalar(YamlParser& parser, SerializationContext& context);

		virtual const std::string& YamlType();

	private:
		Spectrum m_absorption;
	};

}
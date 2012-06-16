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
#include "../Serialization/IYamlSerializable.h"
#include "../Serialization/SerializationHelper.h"
#include "PrecomputedImportanceSampler.h"

namespace Hrt
{

	class Phong : public Material
	{
	public:
		Phong();

		virtual Spectrum CalculateBsdf(const RayLight& incomingRay, 
			const Intersection& intersection, LightingType::Enum lightingType);

		// Specular absorption spectrum.
		Hrt::Spectrum GetSpecular() const { return m_specular; }
		void SetSpecular(Hrt::Spectrum& val) { m_specular = val; }

		// Diffuse absorption spectrum.
		Hrt::Spectrum GetDiffuse() const { return m_diffuse; }
		void SetDiffuse(Hrt::Spectrum& val) { m_diffuse = val; }

		unsigned int GetPowerSpecular() const { return m_powerSpecular; }
		void SetPowerSpecular(unsigned int val) { m_powerSpecular = val; }

		virtual const std::string GetSignature();

		// IYamlSerializable Implementation
		virtual bool ProcessYamlScalar(YamlParser& parser, SerializationContext& context);
		virtual const std::string& YamlType();

	private:
		unsigned int m_powerSpecular;
		Spectrum m_specular;
		Spectrum m_diffuse;
	};
}


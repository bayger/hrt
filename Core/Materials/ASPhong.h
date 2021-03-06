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
#include "PrecomputedImportanceSampler.h"

namespace Hrt
{

	class ASPhong 
		: public Material
	{
	public:
		ASPhong();
		ASPhong(number nu, number nv, number specularFactor, number diffuseFactor);

		virtual Spectrum CalculateBrdf(const RayLight& incomingRay, 
			const Intersection& intersection, LightingType::Enum lightingType);

		// Specular absorption spectrum.
		Hrt::Spectrum GetSpecular() const { return m_specular; }
		void SetSpecular(Hrt::Spectrum& val) { m_specular = val; }

		// Diffuse absorption spectrum.
		Hrt::Spectrum GetDiffuse() const { return m_diffuse; }
		void SetDiffuse(Hrt::Spectrum& val) { m_diffuse = val; }

		// Nu coefficient
		Hrt::number GetNu() const { return m_nu; }
		void SetNu(Hrt::number val) { m_nu = val; }

		// Nv coefficient
		Hrt::number GetNv() const { return m_nv; }
		void SetNv(Hrt::number val) { m_nv = val; }

		// Specular factor in range [0-1]
		Hrt::number GetSpecularFactor() const { return m_specularFactor; }
		void SetSpecularFactor(Hrt::number val) 
		{ 
			assert(val >=0 && val <= 1);
			m_specularFactor = val; 
		}

		// Diffuse factor
		Hrt::number GetDiffuseFactor() const { return m_diffuseFactor; }
		void SetDiffuseFactor(Hrt::number val) 
		{ 
			assert(val >=0 && val <= 1);
			m_diffuseFactor = val; 
		}

		virtual const std::string GetSignature();

		// IYamlSerializable Implementation
		virtual bool ProcessYamlScalar(YamlParser& parser, SerializationContext& context);
		virtual const std::string& YamlType();

	private:
		number m_nu;
		number m_nv;
		number m_specularFactor;
		number m_diffuseFactor;
		Spectrum m_specular;
		Spectrum m_diffuse;
	};

}

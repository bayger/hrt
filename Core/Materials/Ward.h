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
	class Ward : public Material, public enable_shared_from_this<Ward>
	{
	public:
		Ward();
		Ward(number diffuse, number specular, number alphaX, number alphaY);

		// --- Methods ---

		virtual Spectrum CalculateBsdf(const RayLight& incomingRay, 
			const Intersection& intersection, 
			LightingType::Enum lightingType);

		virtual Vector3D SampleVector(number* sample, const Vector3D& outgoingDirection, 
			const Vector3D& tangentU, const Vector3D& tangentV, const Vector3D& n, number& pdf);

		virtual const std::string GetSignature();
    virtual void Initialize() { m_importanceSampler->Precompute(shared_from_this()); }

		// --- Properties ---

		AUTO_GETTER(number, m_diffuse, Diffuse);
		void SetDiffuse(const number val)
		{
			if (val > 1)
				throw InvalidArgumentException("Diffuse factor must be <= 1");

			m_diffuse = val;
			if (m_specular + m_diffuse > 1)
				m_specular = 1 - m_diffuse;
		}
		AUTO_GETTER(number, m_specular, Specular);
		void SetSpecular(const number val)
		{
			if (val > 1)
				throw InvalidArgumentException("Specular factor must be <= 1");

			m_specular = val;
			if (m_diffuse + m_specular > 1)
				m_diffuse = 1 - m_diffuse;
		}
		AUTO_PROPERTY(number, m_alphaX, AlphaX);
		AUTO_PROPERTY(number, m_alphaY, AlphaY);

		// --- IYamlSerializable Implementation ---

		virtual bool ProcessYamlScalar(YamlParser& parser, SerializationContext& context);
		virtual const std::string& YamlType();

	private:
		number m_diffuse;
		number m_specular;
		number m_alphaX;
		number m_alphaY;
		shared_ptr<PrecomputedImportanceSampler> m_importanceSampler;

	};
}


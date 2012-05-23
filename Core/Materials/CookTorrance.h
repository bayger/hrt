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
	/// \brief Namespace contains enum for slope distribution function
	/// Cook-Torrance model may use different slope distribution functions
	/// to achieve different results. CookTorrance class currently supports
	/// only two: Beckmann's and Gaussian (as written in ACM ToG paper).
	namespace SlopeDistribution 
	{
		enum Enum
		{
			Beckmann,
			Gaussian
		};
	}

	/// \brief Material that implements Cook-Torrance reflection model.
	/// Cook-Torrance reflection model is based on microfacet distribution function
	/// and is described in ACM Transactions of Graphics paper titled 'A Reflectance
	/// model for Computer Graphics", 1982, vol. 1, issue 1.
	class CookTorrance : public Material, public enable_shared_from_this<CookTorrance>
	{
	public:
		CookTorrance();
		CookTorrance(number diffuse, number specular, number rms, 
			SlopeDistribution::Enum distribution);

		// --- Methods ---

		virtual Spectrum CalculateBsdf(const RayLight& incomingRay, 
			const Intersection& intersection, 
			LightingType::Enum lightingType);

		virtual Vector3D SampleVector(number* sample, const Vector3D& outgoingDirection, 
			const Vector3D& tangentU, const Vector3D& tangentV, const Vector3D& n, number& pdf, LightingType::Enum& lightingType);

		virtual number CalculatePdf(const Vector3D& outgoingDirection, const Vector3D& tangentU, const Vector3D& tangentV, 
			const Vector3D& n, const Vector3D& incomingDirection, const LightingType::Enum lightingType);

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
		AUTO_PROPERTY(number, m_rms, Rms);
		AUTO_PROPERTY(SlopeDistribution::Enum, m_distribution, Distribution);
		AUTO_PROPERTY(number, m_gaussianC, GaussianC);

		virtual const std::string GetSignature();
    virtual void Initialize() { m_importanceSampler->Precompute(shared_from_this()); }

		// --- IYamlSerializable Implementation ---

		virtual bool ProcessYamlScalar(YamlParser& parser, SerializationContext& context);
		virtual const std::string& YamlType();

	private:
		number m_diffuse;
		number m_specular;
		number m_rms;
		SlopeDistribution::Enum m_distribution;
		number m_gaussianC;

		shared_ptr<PrecomputedImportanceSampler> m_importanceSampler;

		number CalculateG(number nh, number nl, number nv, number vh);
		number CalculateD(number nh, number tan_alpha);
	};
}


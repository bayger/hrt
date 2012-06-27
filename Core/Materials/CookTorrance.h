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
#include "Lipis.h"
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
      Beckmann2,
			Gaussian
		};
	}

	/// \brief Material that implements Cook-Torrance reflection model.
	/// Cook-Torrance reflection model is based on microfacet distribution function
	/// and is described in ACM Transactions of Graphics paper titled 'A Reflectance
	/// model for Computer Graphics", 1982, vol. 1, issue 1.
	class CookTorrance : public Material
	{
	public:
		CookTorrance();
		CookTorrance(number diffuse, number specular, number rms, 
			SlopeDistribution::Enum distribution);

		// --- Methods ---

		virtual Spectrum CalculateBrdf(const RayLight& incomingRay, 
			const Intersection& intersection, 
			LightingType::Enum lightingType);

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
		
		AUTO_PROPERTY(SlopeDistribution::Enum, m_distribution, Distribution);
		AUTO_PROPERTY(number, m_gaussianC, GaussianC);
    AUTO_GETTER(unsigned int, m_beckmannComponents, BeckmannComponents);
    void SetBeckmannComponents(const unsigned int val)
    {
      if (val < 1)
        throw InvalidArgumentException("Beckmann slope component count must be greater than 0");

      m_beckmannComponents = val;
      rmss.clear();
      weights.clear();
    }

		virtual const std::string GetSignature();

	private:
		number m_diffuse;
		number m_specular;
    std::vector<number> rmss;
    std::vector<number> weights;
		SlopeDistribution::Enum m_distribution;
		number m_gaussianC;
    unsigned int m_beckmannComponents;

		number CalculateG(number nh, number nl, number nv, number vh);
		number CalculateD(number nh, number tan_alpha);
	};
}


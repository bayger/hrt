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
#include "CookTorrance.h"
#include "FresnelHelper.h"
#include "../Serialization/SerializationHelper.h"

namespace Hrt
{
	CookTorrance::CookTorrance()
		: m_diffuse(0), m_specular(0), 
			m_distribution(SlopeDistribution::Beckmann), m_gaussianC(1),
      m_beckmannComponents(1)
	{
    m_importanceSamplingType = ImportanceSamplingType::Lipis;
	}

	CookTorrance::CookTorrance( number diffuse, number specular, number rms, 
		SlopeDistribution::Enum distribution)
		: m_distribution(distribution),
		m_gaussianC(1), m_beckmannComponents(1)
	{
		SetDiffuse(diffuse);
		SetSpecular(specular);
    rmss.push_back(rms);
    m_importanceSamplingType = ImportanceSamplingType::Lipis;
	}

	Hrt::Spectrum CookTorrance::CalculateBrdf( const RayLight& incomingRay, 
		const Intersection& intersection, LightingType::Enum lightingType )
	{
		Spectrum result;
		Vector3D n = intersection.Normal.Normalize();
		Vector3D v = -intersection.RayDirection.Normalize();
		Vector3D l = -incomingRay.Direction.Normalize();
		Vector3D h = (v+l).Normalize();

		number vh = v.Dot(h);
		number nl = n.Dot(l);
		number nh = n.Dot(h);
		number nv = n.Dot(v);
		number tan_alpha = Math::Tan(Math::Arcos(nh));

		if (nv < epsilon)
			return result;

		// check if in specular cone
		bool isInSpecularCone = (lightingType & LightingType::IdealSpecular) != 0;

		for(unsigned int lambdaIndex=0; lambdaIndex<Spectrum::LambdaCount; lambdaIndex++)
		{
			// refractive indices and angles
			complexNumber n1(incomingRay.MediumRefractionRe[lambdaIndex],
				incomingRay.MediumRefractionIm[lambdaIndex]);
			complexNumber n2(m_refractionRe[lambdaIndex], m_refractionIm[lambdaIndex]);

			complexNumber complex_cos_theta_t = Math::Sqrt( num(1) - Math::Square(n1/n2)
				* (1 - vh*vh) );
			number cos_theta_t = complex_cos_theta_t.real();

			if (gsl_isnan(cos_theta_t))
			{ // total internal reflection
				result[lambdaIndex] = isInSpecularCone 
					? incomingRay.Radiance[lambdaIndex]
				: 0;
				continue;
			}

			// Fresnel coefficients for polarized light
			number F_s = 0;
			number F_p = 0;
			//FresnelHelper::CalculateFresnel(incomingRay.MediumRefractionRe, 
			//	incomingRay.MediumRefractionIm, m_refractionRe, m_refractionIm,
			//	vh, cos_theta_t, lambdaIndex, F_s, F_p);

      FresnelHelper::CalcFresnel3(m_refractionRe[lambdaIndex],
        m_refractionIm[lambdaIndex], Math::Arcos(vh), F_s, F_p);

			number fresnel = (F_s+F_p) / Consts::TwoPi;
			number D = CalculateD(nh, tan_alpha);

			result[lambdaIndex] = incomingRay.Radiance[lambdaIndex] 
				* ( m_specular * (fresnel/Consts::Pi * CalculateG(nh, nl, nv, vh) * D / (nl*nv)) 
					+ m_diffuse*fresnel/Consts::Pi);
		}

    if (this->GetName() != "Diffuse Only")
    {
      return result;
    }
    number scale = 0.4;
    int tx = (int)Math::Ceiling(scale * intersection.Position.X + 0.5) & 1;
    int ty = (int)Math::Ceiling(scale * intersection.Position.Y + 0.5) & 1;
    int tz = (int)Math::Ceiling(scale * intersection.Position.Z + 0.5) & 1;

		return ((tx+ty+tz) & 1) == 1 ? result : result /4;
	}

	Hrt::number CookTorrance::CalculateG( number nh, number nl, number nv, number vh )
	{
		return Math::Min(num(1), num(2*nh*nv/vh), num(2*nh*nl/vh));
	}

  static number CalculateBeckmann(number tan_alpha, number nh, number rms)
  {
    return num(1/(Math::Square(rms)*Math::Pow(nh,4)) 
      * Math::Exp(-Math::Square(tan_alpha/rms)) );
  }

	Hrt::number CookTorrance::CalculateD( number nh, number tan_alpha )
	{
		switch(m_distribution)
		{
		case SlopeDistribution::Beckmann:
      if (m_beckmannComponents == 1) // NOTE: special case where weight is not needed
			  return CalculateBeckmann(tan_alpha, nh, rmss[0]);
      else
      {
        number d = 0;
        for(unsigned int i=0; i<m_beckmannComponents; i++)
          d += weights[i] * CalculateBeckmann(tan_alpha, nh, rmss[i]);
        return d;
      }

		case SlopeDistribution::Gaussian:
			return Math::Exp(-Math::Square(Math::Arcos(nh)/rmss[0]))*m_gaussianC;
		}

		throw NotSupportedException(
			"Cook-Torrance: Selected slope-distribution is not supported.");
	}

	bool CookTorrance::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "rms")
    {
      number rms;
			parser.ReadScalar(rms);
      rmss.push_back(rms);
    }
    else if (scalarValue == "weight")
    {
      number weight;
      parser.ReadScalar(weight);
      weights.push_back(weight);
    }
		else if (scalarValue == "gaussian-c")
			parser.ReadScalar(m_gaussianC);
		else if (scalarValue == "diffuse")
		{
			number diffuse;
			parser.ReadScalar(diffuse);
			SetDiffuse(diffuse);
		}
		else if (scalarValue == "specular")
		{
			number specular;
			parser.ReadScalar(specular);
			SetSpecular(specular);
		}
		else if (scalarValue == "slope-distribution")
		{
			std::string name;
			parser.ReadScalar(name);
			if (name == "beckmann")
				SetDistribution(SlopeDistribution::Beckmann);
			else if (name == "gaussian")
				SetDistribution(SlopeDistribution::Gaussian);
		}
    else if (scalarValue == "beckmann-components")
    {
      unsigned int u;
      parser.ReadScalar(u);
      SetBeckmannComponents(u);
    }
		else if (scalarValue == "refractive-real")
			m_refractionRe = SerializationHelper::ReadSpectrum(parser);
		else if (scalarValue == "refractive-imaginary")
			m_refractionIm = SerializationHelper::ReadSpectrum(parser);
		else
			return NamedObject::ProcessYamlScalar(parser, context);

		return true;
	}

	static std::string yamlType("cook-torrance");
	const std::string& CookTorrance::YamlType()
	{
		return yamlType;
	}

	const std::string CookTorrance::GetSignature()
	{
		return str(format("%1%:s=%2%,d=%3%,rms=%4%,gc=%5%") % yamlType % m_specular % m_diffuse % rmss[0] % m_gaussianC);
	}
}

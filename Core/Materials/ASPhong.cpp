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
#include "ASPhong.h" 
#include "Lipis.h"

namespace Hrt 
{
	ASPhong::ASPhong() 
		: m_nu(1), 
		m_nv(1), 
		m_specularFactor((number)0.1), 
		m_diffuseFactor((number)0.9),
		m_specular(Spectrum(1)), 
		m_diffuse(Spectrum(1))
	{
    m_importanceSamplingType = ImportanceSamplingType::Lipis;
	}

	ASPhong::ASPhong(number nu, 
		number nv, 
		number specularFactor, 
		number diffuseFactor)
		: m_nu(nu), 
		m_nv(nv), 
		m_specularFactor(specularFactor), 
		m_diffuseFactor(diffuseFactor),
		m_specular(Spectrum(1)), 
		m_diffuse(Spectrum(1))
	{
    m_importanceSamplingType = ImportanceSamplingType::Lipis;
	}

	Spectrum ASPhong::CalculateBrdf(const RayLight& incomingRay,
		const Intersection& intersection, LightingType::Enum lightingType)
	{
		const Spectrum& incomingRadiance = incomingRay.Radiance;
		const Vector3D& incomingDirection = incomingRay.Direction;
		// special case for specular lighting only (for Whitted's ray tracing)
		if (lightingType == LightingType::SpecularOnly)
			return m_specularFactor*m_specular*incomingRadiance;

		Vector3D k1 = -incomingDirection;
		Vector3D k2 = -intersection.RayDirection;
		Vector3D h = (k1+k2).Normalize();

		number nh = intersection.Normal.Dot(h);
		number hk = h.Dot(k1);
		number nk1 = intersection.Normal.Dot(k1);
		number nk2 = intersection.Normal.Dot(k2);
		number hu = h.Dot(intersection.TangentU);
		number hv = h.Dot(intersection.TangentV);

		Spectrum result(0);

		if (nk2 > 0 && nk1 > 0) // reflection
		{
			number e = 1;

			if (nh < 1-epsilon)
				e = (m_nu*(hu*hu) + m_nv*(hv*hv)) / (1-nh*nh);
			else
				e = 1;

			number f = m_specularFactor + (1-m_specularFactor)*Math::Pow(1-hk,5);

			number ps = Math::Sqrt((m_nu+1)*(m_nv+1)) / (8*Consts::Pi) 
				* Math::Pow(nh, e) / (hk*Math::Max(nk1, nk2))
				* f;

			number pd = (28*m_diffuseFactor)/(23*Consts::Pi)*(1-m_specularFactor)
				* (1 - Math::Pow(1-(number)0.5*nk1,5)) 
				* (1 - Math::Pow(1-(number)0.5*nk2,5));

			if (pd > epsilon && (lightingType & LightingType::DiffuseOnly) != 0)
			{
				Spectrum diffuse = pd*m_diffuse;
				result += incomingRadiance*diffuse*(1-m_transparency.Values[0]); // TODO: change
			}
			if (ps > epsilon && (lightingType & LightingType::SpecularOnly) != 0)
			{
				Spectrum specular = ps*m_specular;
				result += incomingRadiance*specular;
			}
		}
		else if (nk2 > 0 && nk1 < 0) // transmission from inside
		{
			result += incomingRadiance;
		}
		else if (nk2 < 0 && nk1 < 0) // complete internal reflection
		{
			result = incomingRadiance;
		}
		else // incoming to inside	
			result = incomingRadiance*(m_transparency);

		return result;
	}
/*
	bool ASPhong::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "specular-factor")
			parser.ReadScalar(m_specularFactor);
		else if (scalarValue == "diffuse-factor")
			parser.ReadScalar(m_diffuseFactor);
		else if (scalarValue == "nu")
			parser.ReadScalar(m_nu);
		else if (scalarValue == "nv")
			parser.ReadScalar(m_nv);
		else if (scalarValue == "specular-absorption")
			m_specular = SerializationHelper::ReadSpectrum(parser);
		else if (scalarValue == "diffuse-absorption")
			m_diffuse = SerializationHelper::ReadSpectrum(parser);
		else
			return Material::ProcessYamlScalar(parser, context);

		return true;
	}

	static std::string yamlType("as-phong");
	const std::string& ASPhong::YamlType()
	{
		return yamlType;
	}
  */
	const std::string ASPhong::GetSignature()
	{
		return str(format("%1%:s=%2%,d=%3%,nu=%4%,nv=%5%,ss=%6%,ds=%7%") % "as" % m_specularFactor % m_diffuseFactor % m_nu % m_nv
			% m_specular.ToString() % m_diffuse.ToString());
	}
}

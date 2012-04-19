/*
H-RT Core - the core of the H-RayTracer ray tracing renderer.
Copyright (c) 2006-08 H-RT Team.

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
#include "Ward.h"
#include "../Serialization/SerializationHelper.h"

namespace Hrt
{
	Ward::Ward()
		: m_specular(num(0.5)), m_diffuse(num(0.5)), m_alphaX(num(0.1)), m_alphaY(num(0.1)),
		m_importanceSampler(new PrecomputedImportanceSampler())
	{
	}

	Ward::Ward( number diffuse, number specular, number alphaX, number alphaY )
		: m_alphaX(alphaX), m_alphaY(alphaY),
		m_importanceSampler(new PrecomputedImportanceSampler())
	{
		SetDiffuse(diffuse);
		SetSpecular(specular);
	}

	Hrt::Spectrum Ward::CalculateBsdf( const RayLight& incomingRay, 
		const Intersection& intersection, LightingType::Enum lightingType )
	{
		Spectrum result;
		Vector3D n = intersection.Normal.Normalize();
		Vector3D v = -intersection.RayDirection.Normalize();
		Vector3D l = -incomingRay.Direction.Normalize();
		Vector3D h = (v+l).Normalize();

		// check if in specular cone
		bool isInSpecularCone = (lightingType & LightingType::IdealSpecular) != 0 ||
			n.Dot(h) > 1-epsilon;

		number delta = Math::Arcos(h.Dot(n));
		Vector3D h_nuv = h.Transform(intersection.TangentU,
			intersection.TangentV, intersection.Normal);
		Vector3D h_nuv_projected = Vector3D(h_nuv.X, h_nuv.Y, 0).Normalize();
		number azimuth = Math::Atan(h_nuv_projected.X, h_nuv_projected.Y);

		number cos_theta_i = n.Dot(l);
		number cos_theta_r = n.Dot(v);

		number s = m_specular / (Math::Sqrt(cos_theta_i*cos_theta_r)*Consts::FourPi*
			m_alphaX*m_alphaY);
		number expo = isInSpecularCone 
			? 1 
			: Math::Exp(-Math::Square( Math::Tan(delta)) 
			* ( Math::Square(Math::Cos(azimuth))/Math::Square(m_alphaX) 
			  + Math::Square(Math::Sin(azimuth))/Math::Square(m_alphaY)) 
			);

		return incomingRay.Radiance * (s*expo + m_diffuse/Consts::Pi);
	}

	bool Ward::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "alpha-x")
			parser.ReadScalar(m_alphaX);
		else if (scalarValue == "alpha-y")
			parser.ReadScalar(m_alphaY);
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
		else if (scalarValue == "refractive-real")
			m_refractionRe = SerializationHelper::ReadSpectrum(parser);
		else if (scalarValue == "refractive-imaginary")
			m_refractionIm = SerializationHelper::ReadSpectrum(parser);
		else
			return NamedObject::ProcessYamlScalar(parser, context);

		return true;
	}

	static std::string yamlType("ward");
	const std::string& Ward::YamlType()
	{
		return yamlType;
	}

	const std::string Ward::GetSignature()
	{
		return str(format("%1%:s=%2%,d=%3%,ax=%4%,ay=%5%") % yamlType % m_specular % m_diffuse % m_alphaX % m_alphaY);
	}

	Hrt::Vector3D Ward::SampleVector(number* sample, const Vector3D& outgoingDirection, const Vector3D& tangentU, const Vector3D& tangentV, const Vector3D& n, number& pdf)
	{
		return m_importanceSampler->SampleVector(sample, outgoingDirection, tangentU, tangentV, n, pdf);
	}

	void Ward::FinishDeserialization()
	{
		m_importanceSampler->Precompute(shared_from_this());
	}
}

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
#include "../Light.h"
#include "../Spectrum.h"
#include "../Vector3D.h"

namespace Hrt
{

	/// Simple point light source.
	class PointLight : public Light
	{
	public:
		PointLight();

		PointLight(const Vector3D& position, const Spectrum& power);

    virtual shared_ptr<Light> Clone();

		// Light overrides

		virtual void Prepare(const Vector3D& target, const Vector3D& normal, RenderingContext& rc)
		{
			Light::Prepare(target, normal, rc);
			m_prepared = true;
		}

		virtual bool GenerateRayLight(RayLight* ray, number& pdf, RenderingContext& rc);

		virtual bool IsDeltaLight() const { return true; }

		virtual bool HasFinitePower() const { return true; }

		virtual Spectrum GetPower() const { return m_power; }

		// Properties

		Hrt::Spectrum GetIntensity() const { return m_intensity; }

		void SetPower(const Hrt::Spectrum& val) 
		{	
			m_power = val; 
			m_intensity = m_power / (4 * Consts::Pi);
		}

		void SetIntensity(const Hrt::Spectrum& val) 
		{	
			m_intensity = val; 
			m_power = m_intensity * (4 * Consts::Pi);
		}

		Hrt::Vector3D GetPosition() const { return m_position; }

		void SetPosition(Hrt::Vector3D val) { m_position = val; }

	private:
		Spectrum m_power;
		Spectrum m_intensity;
		Vector3D m_position;
		bool m_prepared;
	};

}

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
#include "../Vector3D.h"
#include "../Shape.h"
#include "../Box.h"
#include "../LightEmitter.h"
#include "../Sampler.h"
#include "../Spectrum.h"

namespace Hrt
{
	/// Sphere primitive.
	class Sphere : public Shape, public LightEmitter
	{
	public:
		Sphere(void);
		Sphere(SamplerPtr emitterSampler, Spectrum emitterPower);
		Sphere(Vector3D center, number radius);
		Sphere(Vector3D center, number radius, SamplerPtr emitterSampler, Spectrum emitterPower);
		virtual ~Sphere(void);

		virtual bool Intersect(const Ray& ray, Intersection* intersection);

		virtual bool IsLuminaire() { return !m_sampleRadiance.IsZero(); }

		/// Gets sphere radius.
		Hrt::number GetRadius() const { return m_radius; }

		/// Sets sphere radius.
		void SetRadius(Hrt::number val);
		
		/// Gets sphere center.
		Hrt::Vector3D GetCenter() const { return m_center; }

		/// Sets sphere center.
		void SetCenter(Hrt::Vector3D& val);

		void Initialize();

		// LightEmitter Implementation

		virtual uint GetRaysCount() { return m_emitterSampler != NULL ? m_emitterSampler->GetCount() : 0; }

		virtual number GetEmitterArea() { return Consts::FourPi * m_radius * m_radius; }

		virtual void PrepareEmitter(const Vector3D& target, const Vector3D& normal, RenderingContext& rc);

		virtual bool GenerateRayLight(RayLight* ray, number& pdf, RenderingContext& rc);

		virtual void SetPower(Spectrum power);

		virtual void CalculateRadiance(const Vector3D& position, Vector3D& luminaireNormal, Spectrum& radiance);

		virtual number CalculatePdf(const Vector3D& position, RenderingContext& rc);

		// ISupportsConcurrency

		virtual void PrepareForConcurrency(size_t numberOfThreads);


	private:
		struct State
		{
			Vector3D Target;
			Vector3D TargetNormal;
			number TargetDistance;
			number Cone;
			Vector3D U, V, W;
		};

		std::vector<State> m_state;
		BoundingBox m_bbox;
		Vector3D m_center;
		number m_radius;
		SamplerOwnedPtr m_emitterSampler;
		std::vector<SamplerOwnedPtr> m_emitterSamplers;
		Spectrum m_sampleRadiance;
	};

}

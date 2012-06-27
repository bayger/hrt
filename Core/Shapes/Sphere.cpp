/*
* H-RT Core - the core of the H-RayTracer ray tracing renderer.
* Copyright (c) Patryk Bajer, H-RT.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*/

#include "stdafx.h"

#include "Sphere.h"
#include "../Ray.h"
#include "../RayLight.h"
#include "../Intersection.h"
#include "../Matrix.h"
#include "Tangent.h"

namespace Hrt
{

	Sphere::Sphere(void)
	{
	}

	Sphere::Sphere(SamplerPtr emitterSampler, Spectrum emitterPower)
		: m_emitterSampler(emitterSampler)
	{
		SetPower(emitterPower);
	}

	Sphere::Sphere(Vector3D center, number radius)
		: m_center(center), m_radius(radius)
	{
		Initialize();
	}

	Sphere::Sphere(Vector3D center, number radius, SamplerPtr emitterSampler,
		Spectrum emitterPower)
		: m_center(center),
		m_radius(radius),
		m_emitterSampler(emitterSampler)
	{
		SetPower(emitterPower);
	}

	Sphere::~Sphere(void)
	{
	}

	void Sphere::SetCenter(Hrt::Vector3D& val)
	{
		m_center = val;
		Initialize();
	}

	void Sphere::SetRadius(Hrt::number val)
	{
		m_radius = val;
		Initialize();
	}

	bool Sphere::Intersect(const Ray& ray, Intersection* intersection)
	{
		// smarter version :)
		Vector3D center = m_center - ray.Position;

		number a = ray.Direction.X*ray.Direction.X + ray.Direction.Y*ray.Direction.Y
			+ ray.Direction.Z*ray.Direction.Z;
		number b = -2*( ray.Direction.X*center.X + ray.Direction.Y*center.Y
			+ ray.Direction.Z*center.Z );
		number c = center.X*center.X + center.Y*center.Y + center.Z*center.Z
			- m_radius*m_radius;

		number a2 = a+a;

		number delta = b*b - 2*a2*c;

		if (delta < 0)
			return false;

		number sd = Math::Sqrt(delta);
		number t1 = (-b + sd) / (a2);
		number t2 = (-b - sd) / (a2);
		number t = t1 > t2 && t2 > 0 ? t2 : t1;

		if (t > 0)
		{
			intersection->Position.X = ray.Position.X + t*ray.Direction.X;
			intersection->Position.Y = ray.Position.Y + t*ray.Direction.Y;
			intersection->Position.Z = ray.Position.Z + t*ray.Direction.Z;
			intersection->Normal = (intersection->Position-m_center).Normalize();
			intersection->DistanceFromRayOrigin = t;

			ComputeTangents(intersection->Normal, intersection->TangentU, intersection->TangentV);

			return true;
		}

		return false;
	}

	void Sphere::PrepareEmitter(const Vector3D& target, const Vector3D& normal, RenderingContext& rc)
	{
		State& state = m_state[rc.GetThreadId()];

		state.Target = target;
		state.TargetNormal = normal;
		m_emitterSamplers[rc.GetThreadId()]->Shuffle(rc.GetRandomizer());
		state.TargetDistance = (m_center-target).Length();
		number rd = m_radius/state.TargetDistance;
		state.Cone = sqrt(1 - (rd*rd));
		state.W = (m_center - state.Target).Normalize();
		Vector3D t;
		if(fabs(state.W.X) >= fabs(state.W.Y))
			t.Set(0, 1, 0);
		else
			t.Set(1, 0, 0);
		state.U = state.W.Cross(t).Normalize();
		state.V = state.W.Cross(state.U).Normalize();
	}

	static number HitSphereDistance(number theta, number d, number r)
	{
		if (theta < epsilon) // special case for v.distant lights
			return d-r;

		number lx = cos(theta);
		number ly = sin(theta);

		number b = -2*d*lx;
		number a = lx*lx + ly*ly;
		number c = d*d - r*r;

		return (-b - sqrt(b*b - 4*a*c)) / (2*a);
	}

	bool Sphere::GenerateRayLight(RayLight* ray, number& pdf, RenderingContext& rc)
	{
		State& state = m_state[rc.GetThreadId()];

		number uv[2];
		if (!m_emitterSamplers[rc.GetThreadId()]->NextSample(uv, rc.GetRandomizer()))
			return false;

		number theta = acos(1.0 - uv[0] + uv[0] * state.Cone);
		number phi = Consts::TwoPi * uv[1];

		ray->Direction = -Vector3D::FromSpherical(phi, theta, state.U, state.V, state.W);
		number d = HitSphereDistance(theta, state.TargetDistance, m_radius);
		ray->Position = state.Target - ray->Direction * d;
		ray->Radiance = m_sampleRadiance;
		ray->LightNormal = (ray->Position - m_center).Normalize();

		pdf = ray->LightNormal.Dot(ray->Direction) / 
			((state.Target - ray->Position).LengthSquared() * Consts::TwoPi * (1.0 - state.Cone)); 

		return true;
	}

	void Sphere::SetPower(Spectrum power)
	{
		LightEmitter::SetPower(power);
		m_sampleRadiance = m_emitterPower / ( GetEmitterArea() * Consts::TwoPi );
	}
/*
	static std::string yamlType("sphere");
	const std::string& Sphere::YamlType()
	{
		return yamlType;
	}

	bool Sphere::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "center")
			m_center = SerializationHelper::ReadVector3D(parser);
		else if (scalarValue == "radius")
			parser.ReadScalar(m_radius);
		else if (scalarValue == "emitter-power")
			SetPower(SerializationHelper::ReadSpectrum(parser));
		else if (scalarValue == "emitter-sampler")
		{
			std::string scalarType = parser.CurrentTag();
			m_emitterSampler = Singleton<SamplerSerializer>::Instance().Deserialize(scalarType,
				parser, context);
		}
		else
			return Shape::ProcessYamlScalar(parser, context);

		return true;
	}

	void Sphere::FinishDeserialization()
	{
		Initialize();
	}
  */
	void Sphere::Initialize()
	{
		m_bbox = BoundingBox(m_center.X-m_radius, m_center.Y-m_radius, m_center.Z-m_radius,
			m_center.X+m_radius, m_center.Y+m_radius, m_center.Z+m_radius);
	}

	void Sphere::CalculateRadiance(const Vector3D& position, Vector3D& luminaireNormal, Spectrum& radiance)
	{
		radiance = m_sampleRadiance;
		luminaireNormal = (position - m_center).Normalize();
	}

	number Sphere::CalculatePdf(const Vector3D& position, RenderingContext& rc)
	{
		State& state = m_state[rc.GetThreadId()];

		Vector3D lightNormal = (position-m_center).Normalize();
		Vector3D direction = (state.Target-position).Normalize();

		return lightNormal.Dot(direction) / 
			((state.Target - position).LengthSquared() * Consts::TwoPi * (1.0 - state.Cone)); 

	}

	void Sphere::PrepareForConcurrency(size_t numberOfThreads)
	{
		if (m_emitterSampler == 0)
			return;

		for(size_t i=0; i<numberOfThreads; i++)
			m_emitterSamplers.push_back(m_emitterSampler->Clone());

		m_state.resize(numberOfThreads);
	}

  void Sphere::SetEmitterSampler(SamplerPtr sampler)
  {
    m_emitterSampler = sampler;
  }

}

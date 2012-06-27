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

#include "Cylinder.h"
#include "../Intersection.h"
#include "../Ray.h"
#include "Tangent.h"

namespace Hrt
{

	Cylinder::Cylinder(Hrt::number height, Hrt::number radius, Matrix transform)
		: m_height(height), m_radius(radius), m_transform(transform)
	{
		Initialize();
	}

	Cylinder::Cylinder()
		: m_height(1), m_radius(1)
	{
		Initialize();
	}

	void Cylinder::SetTransform(Hrt::Matrix val) 
	{ 
		m_transform = val; 
		m_inverseTransform = m_transform;
		m_inverseTransform.InverseFast();
	}

	bool Cylinder::Intersect(const Ray& ray, Intersection* intersection)
	{
		Vector3D rayPos = ray.Position*m_inverseTransform;
		Vector3D rayDir = ray.Direction*m_inverseTransform - Vector3D::Zero*m_inverseTransform;

		number x0 = rayPos.X;
		number z0 = rayPos.Z;

		number a = rayDir.X*rayDir.X + rayDir.Z*rayDir.Z;
		number a2 = a+a;
		number b = 2*(rayDir.X*x0 + rayDir.Z*z0);
		number c = x0*x0 + z0*z0 - m_radius*m_radius;

		number delta = b*b - 2*a2*c;

		if (delta < 0)
			return false;
;
		number sd = Math::Sqrt(delta);
		number t1 = (-b + sd) / (a2);
		number t2 = (-b - sd) / (a2);
		number t = -1;

		number y1 = rayPos.Y + t1*rayDir.Y;

		if (y1 >= 0 && y1 <= m_height && t1 > 0)
			t = t1;

		number y2 = rayPos.Y + t2*rayDir.Y;

		if ((t2 < t || t == -1) && y2 >= 0 && y2 <= m_height && t2 > 0)
			t = t2;

		if (t > 0)
		{
			Vector3D normal(x0 + rayDir.X*t, 0, z0 + rayDir.Z*t);
			intersection->Position.X = ray.Position.X + t*ray.Direction.X;
			intersection->Position.Y = ray.Position.Y + t*ray.Direction.Y;
			intersection->Position.Z = ray.Position.Z + t*ray.Direction.Z;
			intersection->Normal = (normal.Normalize() * m_transform - Vector3D::Zero * m_transform);
			intersection->DistanceFromRayOrigin = t;

			ComputeTangents(intersection->Normal, intersection->TangentU, intersection->TangentV);

			return true;
		}
		else
			return false;
	}
  /*
	static std::string yamlType("cylinder");
	const std::string& Cylinder::YamlType()
	{
		return yamlType;
	}

	bool Cylinder::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "radius")
			parser.ReadScalar(m_radius);
		else if (scalarValue == "height")
			parser.ReadScalar(m_height);
		else if (scalarValue == "transform")
			m_transform.Deserialize(parser, context);
		else
			return Shape::ProcessYamlScalar(parser, context);

		return true;
	}

  void Cylinder::FinishDeserialization()
  {
    Initialize();
  }
  */

	void Cylinder::Initialize()
	{
		m_inverseTransform = m_transform;
		m_inverseTransform.InverseFast();
	}
}

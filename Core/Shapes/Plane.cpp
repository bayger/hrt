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

#include "Plane.h"
#include "../Intersection.h"
#include "../Ray.h"
#include "Tangent.h"

namespace Hrt
{

	Plane::Plane(void)
		: m_normal(Vector3D::Zero), m_distance(0)
	{
	}

	Plane::Plane(Vector3D normal, number d)
		: m_normal(normal), m_distance(d)
	{
	}

	Plane::~Plane(void)
	{
	}

	bool Plane::Intersect(const Ray& ray, Intersection* intersection)
	{
		number r = (m_normal.X*ray.Direction.X + m_normal.Y*ray.Direction.Y + m_normal.Z*ray.Direction.Z);
		number t = 0;

		if (r != 0)
			t = (number)(-(m_distance+m_normal.X*ray.Position.X + m_normal.Y*ray.Position.Y + m_normal.Z*ray.Position.Z) / r);

		if (t > 0)
		{
			intersection->Normal = m_normal;
			intersection->Position.X = ray.Position.X + t*ray.Direction.X;
			intersection->Position.Y = ray.Position.Y + t*ray.Direction.Y;
			intersection->Position.Z = ray.Position.Z + t*ray.Direction.Z;
			intersection->DistanceFromRayOrigin = t;

			// calculate tangent vectors
			ComputeTangents(intersection->Normal, intersection->TangentU, intersection->TangentV);

			return true;
		}

		return false;
	}

  /*
	static std::string yamlType("plane");
	const std::string& Plane::YamlType()
	{
		return yamlType;
	}

	bool Plane::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "normal")
			Normal = SerializationHelper::ReadVector3D(parser);
		else if (scalarValue == "distance")
			parser.ReadScalar(D);
		else
			return Shape::ProcessYamlScalar(parser, context);

		return true;
	}
  */

}

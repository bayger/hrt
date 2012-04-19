/*
H-RT Core - the core of the H-RayTracer ray tracing renderer.
Copyright (c) 2006-2010 H-RT Team.

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

#include "Disc.h"
#include "../Vector3D.h"
#include "../Ray.h"
#include "../Intersection.h"
#include "Tangent.h"

namespace Hrt
{

	Disc::Disc(number radius, Matrix& transform)
		: m_radius(radius),
		m_transform(transform)
	{
		Initialize();
	}

	Disc::Disc()
		: m_radius(1)
	{
		m_transform.Identity();
	}

	bool Disc::Intersect(const Ray& ray, Intersection* intersection)
	{
		Vector3D rayPos = ray.Position * m_inverseTransform;
		Vector3D rayDir = ray.Direction * m_inverseTransform - Vector3D::Zero * m_inverseTransform;

		number t = -rayPos.Y / rayDir.Y;

		if (t > 0)
		{
			number x = rayPos.X + t*rayDir.X;
			number z = rayPos.Z + t*rayDir.Z;

			if ((x*x + z*z) < m_radius*m_radius)
			{
				intersection->DistanceFromRayOrigin = t;
				intersection->Normal = Vector3D::UnitY;// * m_transform - Vector3D::Zero * m_transform;
				intersection->Position = Vector3D(x, rayPos.Y + t*rayDir.Y, z) * m_transform;

				ComputeTangents(intersection->Normal, intersection->TangentU, intersection->TangentV);

				return true;
			}
		}

		return false;
	}

	static std::string yamlType("disc");
	const std::string& Disc::YamlType()
	{
		return yamlType;
	}

	bool Disc::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "radius")
			parser.ReadScalar(m_radius);
		else if (scalarValue == "transform")
			m_transform.Deserialize(parser, context);
		else
			return Shape::ProcessYamlScalar(parser, context);

		return true;
	}

	void Disc::Initialize()
	{
		m_inverseTransform = m_transform;
		m_inverseTransform.InverseFast();
	}

	void Disc::FinishDeserialization()
	{
		Initialize();
	}
}

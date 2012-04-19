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

#include "Triangle.h"
#include "../Ray.h"
#include "../RayLight.h"
#include "../Intersection.h"
#include "../Matrix.h"
#include "../Serialization/SerializationHelper.h"

namespace Hrt
{

	Triangle::Triangle(void)
	{
	}

	Triangle::Triangle(Vector3D a,Vector3D b,Vector3D c) : m_a(a), m_b(b), m_c(c)
	{
		Initialize();
	}

	Triangle::~Triangle(void)
	{
	}

	bool Triangle::Intersect(const Ray& ray, Intersection* intersection)
	{
		Vector3D edge1, edge2, norm, tvec, pvec, qvec;
		number det, inv_det;

		edge1 = m_b - m_a;
		edge2 = m_c - m_a;
		norm = edge1.Cross(edge2).Normalize();
		if (norm.Dot(ray.Direction) > 0)
			norm = -norm;

		pvec = ray.Direction.Cross(edge2);

		det = edge1.Dot(pvec);
		if(det < epsilon && det > -epsilon)
			return false;

		inv_det	= 1 / det;

		tvec = ray.Position - m_a;
		number u = tvec.Dot(pvec) * inv_det;
		if(u < 0 || u > 1)
			return false;

		qvec = tvec.Cross(edge1);
		number v = ray.Direction.Dot(qvec) * inv_det;
		if(v < 0 || u + v > 1)
			return false;

		number t = edge2.Dot(qvec) * inv_det;

		intersection->Position.X = ray.Position.X + t*ray.Direction.X;
		intersection->Position.Y = ray.Position.Y + t*ray.Direction.Y;
		intersection->Position.Z = ray.Position.Z + t*ray.Direction.Z;
		intersection->Normal = norm;
		intersection->DistanceFromRayOrigin = t;
		intersection->TangentU = edge1.Normalize();
		intersection->TangentV = norm.Cross(intersection->TangentU).Normalize();

		return true;
	}

	static std::string yamlType("triangle");
	const std::string& Triangle::YamlType()
	{
		return yamlType;
	}

	bool Triangle::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "a")
			m_a = SerializationHelper::ReadVector3D(parser);
		else if (scalarValue == "b")
			m_b = SerializationHelper::ReadVector3D(parser);
		else if (scalarValue == "c")
			m_c = SerializationHelper::ReadVector3D(parser);
		else
			return Shape::ProcessYamlScalar(parser, context);

		return true;
	}

	void Triangle::Initialize()
	{
		m_bbox = BoundingBox(
			Math::Min(m_a.X, m_b.X, m_c.X), Math::Min(m_a.Y, m_b.Y, m_c.Y), 
			Math::Min(m_a.Z, m_b.Z, m_c.Z),
			Math::Max(m_a.X, m_b.X, m_c.X), Math::Max(m_a.Y, m_b.Y, m_c.Y), 
			Math::Max(m_a.Z, m_b.Z, m_c.Z));
	}

	void Triangle::FinishDeserialization()
	{
		Initialize();
	}
}

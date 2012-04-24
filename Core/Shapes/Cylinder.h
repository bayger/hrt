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
#include "../Shape.h"
#include "../Matrix.h"

namespace Hrt
{

	class Cylinder : public Shape
	{
	public:
		Cylinder();
		Cylinder(number height, number radius, Matrix transform);

		virtual bool Intersect(const Ray& ray, Intersection* intersection);

		Hrt::number GetHeight() const { return m_height; }

		void SetHeight(Hrt::number val) { m_height = val; }

		Hrt::number GetRadius() const { return m_radius; }

		void SetRadius(Hrt::number val) { m_radius = val; }

		Hrt::Matrix GetTransform() const { return m_transform; }

		void SetTransform(Hrt::Matrix val);


		// IYamlSerializable Implementation

		virtual const std::string& YamlType();
		virtual bool ProcessYamlScalar(YamlParser& parser, SerializationContext& context);
		virtual void FinishDeserialization();

	private:
		number m_height;
		number m_radius;
		Matrix m_transform;
		Matrix m_inverseTransform;

		void Initialize();
	};

}

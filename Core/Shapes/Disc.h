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
#pragma once
#include "../Common.h"
#include "../Shape.h"
#include "../Matrix.h"

namespace Hrt
{
	/// Disc shape.
	class Disc : public Shape
	{
	public:
		Disc();
		Disc(number radius, Matrix& transform);

		virtual bool Intersect(const Ray& ray, Intersection* intersection);

		// IYamlSerializable Implementation
		virtual const std::string& YamlType();
		virtual bool ProcessYamlScalar(YamlParser& parser, SerializationContext& context);
		virtual void FinishDeserialization();

	private:
		number m_radius;
		Matrix m_transform;
		Matrix m_inverseTransform;

		void Initialize();
	};

}

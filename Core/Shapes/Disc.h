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
	/// Disc shape.
	class Disc : public Shape
	{
	public:
		Disc();
		Disc(number radius, Matrix& transform);

		virtual bool Intersect(const Ray& ray, Intersection* intersection);

    AUTO_PROPERTY(number, m_radius, Radius);

    AUTO_PROPERTY(Matrix, m_transform, Transform);

	private:
		number m_radius;
		Matrix m_transform;
		Matrix m_inverseTransform;

		void Initialize();
	};

}

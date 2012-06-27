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
#include "../Vector3D.h"

namespace Hrt
{

	/// Implements plane shape with Ax+By+Cz+D=0 equation.
	class Plane : public Shape
	{
	public:
		Plane(void);
		Plane(Vector3D normal, number d);
		virtual ~Plane(void);

		virtual bool Intersect(const Ray& ray, Intersection* intersection);

		// TODO: hide the following fields!

		/// Normal to the plane (A,B,C coefficients)
		Vector3D Normal;

		/// Coefficient D of plane's equation
		number D;
	};

}

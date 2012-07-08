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
	/// Triangle primitive.
	class Triangle : public Shape
	{
	public:
		Triangle(void);
		Triangle(Vector3D a,Vector3D b,Vector3D c);
		virtual ~Triangle(void);

		virtual bool Intersect(const Ray& ray, Intersection* intersection);

    AUTO_PROPERTY(Vector3D, m_a, PointA);

    AUTO_PROPERTY(Vector3D, m_b, PointB);

    AUTO_PROPERTY(Vector3D, m_c, PointC);

	private:
		BoundingBox m_bbox;
		Vector3D m_a;
		Vector3D m_b;
		Vector3D m_c;

		void Initialize();
	};

}

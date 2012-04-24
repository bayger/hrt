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
#include "../Geometry.h"

namespace Hrt
{

	/// This is a geometry without any accelerating data structure. 
	/// It provides simple brute-force intersection tests.
	class PlainGeometry : public Geometry
	{
	public:
		virtual void Preprocess() 
		{
			m_altered = false;
		}

		virtual bool Intersect(const Ray& ray, Intersection* intersection);

		virtual bool CheckVisibility(const Vector3D& a, const Vector3D& b);
	};

}

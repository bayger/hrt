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
#include "NamedObject.h"
#include "ISupportsConcurrency.h"

namespace Hrt
{
	struct Intersection;
	struct Ray;

	/// Base class for all 3D objects (sphere, plane, etc.)
	class Shape
		: public NamedObject,
			public ISupportsConcurrency
	{
	public:
		Shape(void);
		virtual ~Shape(void);

		virtual bool Intersect(const Ray& ray, Intersection* intersection)=0;

		virtual bool IsLuminaire() { return false; }
	};

	/// Reference to const shared-pointer of Shape (used as params and returns)
	typedef const shared_ptr<Shape>& ShapePtr;
	
	/// Shared-pointer of Shape (version for owners)
	typedef shared_ptr<Shape> ShapeOwnedPtr;
}

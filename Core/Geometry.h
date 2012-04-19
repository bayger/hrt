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
#include <vector>
#include "Common.h"
#include "Primitive.h"
#include "Vector3D.h"

namespace Hrt
{
	struct Ray;
	struct Intersection;

	/// A geometry represents a collection of primitives. It does intersection stuff.
	/// This is a base class for subclasses of geometry processing classes.
	class Geometry
	{
	public:
		Geometry();
		
		virtual ~Geometry();

		/// Prepares geometry for future usage.
		virtual void Preprocess()=0;

		/// Finds nearest intersection of given ray with geometry.
		virtual bool Intersect(const Ray& ray, Intersection* intersection)=0;

		/// Checks whether point b is visible from point b and vice versa.
		/// \param a Point in world space
		/// \param b Point in world space
		/// \return Returns true if there is no obstacle between a and b.
		virtual bool CheckVisibility(const Vector3D& a, const Vector3D& b)=0;

		/// Adds primitive to the geometry collection.
		void AddPrimitive(PrimitivePtr primitive);

		/// Removes particular primitive from geometry.
		void RemovePrimitive(PrimitivePtr primitive);

		/// Returns number of primitives in this geometry.
		uint GetPrimitiveCount();

		/// Returns primitive from geometry collection.
		PrimitivePtr operator[](uint index);

		/// Removes all primitives from collection.
		void Clear();

	protected:
		bool m_altered;
		std::vector< PrimitiveOwnedPtr > m_primitives;
	};

	/// Reference to const shared-pointer of Geometry (used as params and returns)
	typedef const shared_ptr<Geometry>& GeometryPtr;
	
	/// Shared-pointer of Geometry (version for owners)
	typedef shared_ptr<Geometry> GeometryOwnedPtr;
}

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

#include "stdafx.h"

#include "PlainGeometry.h"
#include "../Intersection.h"
#include "../Shape.h"
#include "../Ray.h"

namespace Hrt
{

	bool PlainGeometry::Intersect(const Ray& ray, Intersection* intersection)
	{

		Intersection i1, i2;
		Intersection* tempIntersection = &i1;
		Intersection* bestIntersection = &i2;
		bestIntersection->DistanceFromRayOrigin = 0;

		std::vector< PrimitiveOwnedPtr >::iterator it = m_primitives.begin();
		while( it != m_primitives.end() )
		{
			ShapePtr shape = (*it)->GetShape();
			if (shape->Intersect(ray, tempIntersection))
			{
				if (bestIntersection->DistanceFromRayOrigin == 0 || (bestIntersection->DistanceFromRayOrigin > tempIntersection->DistanceFromRayOrigin
					&& tempIntersection->DistanceFromRayOrigin > epsilon))
				{
					Intersection* swapValue = bestIntersection;
					bestIntersection = tempIntersection;
					tempIntersection = swapValue;

					bestIntersection->HitPrimitive = (*it).get();
				}
			}

			it++;
		}

		if (bestIntersection->DistanceFromRayOrigin > 0)
		{
			*intersection = *bestIntersection;
			intersection->RayDirection = ray.Direction;

			if (ray.Direction.Dot(intersection->Normal) > 0)
				intersection->Normal = -intersection->Normal;

			return true;
		}
		else
			return false;
	}

	bool PlainGeometry::CheckVisibility(const Vector3D& a, const Vector3D& b)
	{
		Intersection intersection;
		Ray ray;
		Vector3D ba = b-a;
		number distance = ba.Length() - epsilon*5;
		ray.Direction = ba.Normalize();
		ray.Position = a;


		bool obstacle = false;
		if (Intersect(ray, &intersection))
		{
			obstacle = intersection.DistanceFromRayOrigin < distance;
		}

		return !obstacle;
	}

}

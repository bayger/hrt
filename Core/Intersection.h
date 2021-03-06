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
#include "Vector3D.h"

namespace Hrt
{
	class Primitive;
	class Scene;

	struct Intersection
	{
		Vector3D RayDirection;
		Vector3D Position;
		Vector3D Normal;
		Vector3D TangentU;
		Vector3D TangentV;
		number DistanceFromRayOrigin;
		Primitive* HitPrimitive;
	};

}

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
#include "Common.h"
#include "Vector3D.h"
#include "Spectrum.h"

namespace Hrt
{
	struct Ray
	{
		/// Origin of the ray.
		Vector3D Position;

		/// Direction of the ray.
		Vector3D Direction;

		/// Current medium refractive index.
		Spectrum MediumRefractionRe;
		Spectrum MediumRefractionIm;

		/// Total distance (including bounces)
		number TotalDistance;

		Ray() : MediumRefractionRe(1), MediumRefractionIm(0), TotalDistance(0) {}
	};

}

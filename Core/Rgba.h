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
#include "CieXyz.h"
namespace Hrt
{

	/// Single RGB+Alpha pixel struct.
	struct Rgb
	{
		number R;
		number G;
		number B;

		Rgb() : R(0), G(0), B(0)
		{
		}

		Rgb(number r, number g, number b)
			: R(r), G(g), B(b)
		{
		}

		void Set(number r, number g, number b)
		{
			R = r; G = g; B = b;
		}

		void FromCieXyz(CieXyz& xyz)
		{
			R = (number)(3.240479*xyz.X + -1.537150*xyz.Y + -0.498535*xyz.Z);
			G = (number)(-0.969256*xyz.X + 1.875992*xyz.Y + 0.041556*xyz.Z);
			B = (number)(0.055648*xyz.X + -0.204043*xyz.Y + 1.057311*xyz.Z);

			if (R < 0) R = 0;
			if (G < 0) G = 0;
			if (B < 0) B = 0;
		}

		CieXyz ToCieXyz()
		{
			CieXyz result;
			result.X = (number)(R*0.412453  +G*0.357580  +B*0.180423);
			result.Y = (number)(R*0.212671  +G*0.715160  +B*0.072169);
			result.Z = (number)(R*0.019334  +G*0.119193  +B*0.950227);

			return result;
		}

		// TODO: add From/ToCieXyz with different white points and RGB spaces
	};

}

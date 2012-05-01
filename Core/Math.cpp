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
#include "Math.h"

namespace Hrt
{

	number Math::Erfc(number x)
	{
    int inf = gsl_isinf(x);
		return inf == 0 ? num(gsl_sf_erfc(x)) : -(inf-1);
	}

	Hrt::number Math::Factorial( unsigned int i )
	{
		return num(gsl_sf_fact(i));
	}

	Hrt::number Math::Taylor( number x, int n )
	{
		return num(gsl_sf_taylorcoeff(n, x));
  }

}

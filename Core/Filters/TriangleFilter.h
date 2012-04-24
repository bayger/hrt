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
#include "../Filter.h"

namespace Hrt
{

	/// Simple triangle filter.
	class TriangleFilter : public Filter
	{
	public:
		TriangleFilter(int width=1, int height=1);

		virtual number Calculate(number x, number y);

		virtual const std::string& YamlType();
	};

}

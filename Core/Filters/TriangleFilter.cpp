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

#include "TriangleFilter.h"
#include "../Math.h"

namespace Hrt
{

	TriangleFilter::TriangleFilter(number width, number height)
		: Filter(width, height)
	{
	}

	number TriangleFilter::Calculate(number x, number y)
	{
		bool inRange = (x > -m_width && x < m_width && y > -m_height && y < m_height);

		if (inRange)
		{
			number h = 1 - (Math::Abs(x)/m_width);
			number v = 1 - (Math::Abs(y)/m_height);
			return h*v;
		}
		
		return 0;
	}

	static std::string yamlType("triangle-filter");
	const std::string& TriangleFilter::YamlType()
	{
		return yamlType;
	}
}

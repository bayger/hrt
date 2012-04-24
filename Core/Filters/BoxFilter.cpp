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

BoxFilter.cpp
Implementation of the box-filter.

*/

#include "stdafx.h"

#include "BoxFilter.h"

namespace Hrt
{

	BoxFilter::BoxFilter(int boxSize)
		: Filter(boxSize, boxSize)
	{
	}

	number BoxFilter::Calculate(number x, number y)
	{
		return (number)(x > -m_width && x < m_width 
			&& y > -m_height && y < m_height ? 1 : 0);
	}

	std::string yamlType("box-filter");
	const std::string& BoxFilter::YamlType()
	{
		return yamlType;
	}
}

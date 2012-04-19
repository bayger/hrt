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

#include "stdafx.h"

#include "../Math.h"
#include "GaussianFilter.h"

namespace Hrt
{

	GaussianFilter::GaussianFilter(int width, int height, number alpha)
		: Filter(width, height),
		m_alpha(alpha),
		m_expX( Math::Exp( -m_alpha * m_width * m_width ) ),
		m_expY( Math::Exp( -m_alpha * m_height * m_height ) )
	{
	}

	number GaussianFilter::Calculate(number x, number y)
	{
		if (x > m_width || x < -m_width)
			return 0;
		if (y > m_height || y < -m_height)
			return 0;

		return ( Math::Max(zero, Math::Exp(-m_alpha * x * x) - m_expX)  )
			* ( Math::Max(zero, Math::Exp(-m_alpha * y * y) - m_expY) );
	}

	static std::string yamlType("gaussian-filter");
	const std::string& GaussianFilter::YamlType()
	{
		return yamlType;
	}
}

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
#include "../Common.h"
#include "../Filter.h"

namespace Hrt
{
	/// Gaussian filter.
	class GaussianFilter : public Filter
	{
	public:
		GaussianFilter(int width = 1, int height = 1, number alpha = 1);

		virtual number Calculate(number x, number y);

		virtual const std::string& YamlType();

	private:
		number m_alpha;
		number m_expX;
		number m_expY;
	};

}

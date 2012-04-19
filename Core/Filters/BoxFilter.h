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
#include "../Serialization/IYamlSerializable.h"

namespace Hrt
{

	/// Most primitive image filter - a box filter.
	class BoxFilter : public Filter
	{
	public:
		BoxFilter(int boxSize = 1);

		virtual number Calculate(number x, number y);

		// IYamlSerializable Implementation
		virtual const std::string& YamlType();
	};

}

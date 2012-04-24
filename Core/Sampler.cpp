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
#include "Sampler.h"

namespace Hrt
{

	Sampler::Sampler(int dimension)
		: m_dimension(dimension)
	{
	}

	Sampler::Sampler()
		: m_dimension(0)
	{

	}

	Sampler::~Sampler(void)
	{
	}

	bool Sampler::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "dimension")
			parser.ReadScalar(m_dimension);
		else
			return false;

		return true;
	}
}

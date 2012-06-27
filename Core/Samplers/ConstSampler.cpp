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

#include "ConstSampler.h"

namespace Hrt
{
	ConstSampler::ConstSampler()
		: Sampler(1), m_isReset(true)
	{}

	ConstSampler::ConstSampler(int dimension)
		: Sampler(dimension), m_isReset(true)
	{
	}

	ConstSampler::~ConstSampler(void)
	{
	}

	bool ConstSampler::NextSample(number *sample, RandomizerPtr randomizer)
	{
		if (!m_isReset)
			return false;

		for(int i=0; i<m_dimension; i++)
			sample[i] = (number)0.5;

		m_isReset = false;
		return true;
	}

	void ConstSampler::Shuffle(RandomizerPtr randomizer)
	{
		m_isReset = true;
	}
/*
	static std::string yamlType("const-sampler");
	const std::string& ConstSampler::YamlType()
	{
		return yamlType;
	}

	bool ConstSampler::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "value")
		{
			number val;
			parser.ReadScalar(val);
		}
		else if (scalarValue.size() == 0)
			;
		else
			return Sampler::ProcessYamlScalar(parser, context);

		return true;
	}
  */
}

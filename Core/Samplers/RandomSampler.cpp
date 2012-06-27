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

#include "RandomSampler.h"
#include "../Math.h"

namespace Hrt
{

	RandomSampler::RandomSampler(int dimension, int noSamples)
		: Sampler(dimension), m_noSamples(noSamples), m_currentSample(0)
	{
	}

	RandomSampler::RandomSampler()
		: m_noSamples(0), m_currentSample(0)
	{

	}

	void RandomSampler::Shuffle(RandomizerPtr randomizer)
	{
		m_currentSample = 0;
	}

	bool RandomSampler::NextSample(number *sample, RandomizerPtr randomizer)
	{
		if (m_currentSample >= m_noSamples)
			return false;

		for(int i=0; i<m_dimension; i++)
			sample[i] = randomizer->Random(0, 1);

		m_currentSample++;
		return true;
	}

  /*
	static std::string yamlType("random-sampler");
	const std::string& RandomSampler::YamlType()
	{
		return yamlType;
	}

	bool RandomSampler::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "count")
			parser.ReadScalar(m_noSamples);
		else
			return Sampler::ProcessYamlScalar(parser, context);

		return true;
	}
  */
}

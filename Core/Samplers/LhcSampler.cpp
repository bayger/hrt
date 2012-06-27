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

#include "LhcSampler.h"
#include "../Math.h"

namespace Hrt
{

	LhcSampler::LhcSampler(int dimension, int noSamples)
		: Sampler(dimension), 
		m_currentSample(noSamples), 
		m_noSamples(noSamples),
		m_places(new int[noSamples*dimension])
	{
	}

	LhcSampler::LhcSampler()
		: m_currentSample(0),
		m_noSamples(0),
		m_places(NULL)
	{

	}

	LhcSampler::~LhcSampler()
	{
		delete [] m_places;
		m_places = NULL;
	}

	bool LhcSampler::NextSample(number* sample, RandomizerPtr randomizer)
	{
		if (m_currentSample >= m_noSamples)
			return false;

		number recip = 1/(number)m_noSamples;
		number halfr = recip/2;

		for(int i=0; i<m_dimension; i++)
			sample[i] = (number)( m_places[i*m_noSamples + m_currentSample] * recip + randomizer->Random(0., 1.)*recip);

		m_currentSample++;
		return true;
	}

	void LhcSampler::Shuffle(RandomizerPtr randomizer)
	{
		// initialize with diagonal places
		for(int i=0; i<m_dimension; i++)
		{
			for(int j=0; j<m_noSamples; j++)
				m_places[i*m_noSamples + j] = j;
		}

		// shuffle indices
		for(int i=0; i<m_dimension; i++)
			for(int j=0; j<m_noSamples; j++)
			{
				int index = randomizer->Random(m_noSamples-1);
				int oldPos = m_places[i*m_noSamples + index];
				m_places[i*m_noSamples + index] = m_places[i*m_noSamples + j];
				m_places[i*m_noSamples + j] = oldPos;

			}

		m_currentSample = 0;
	}
/*
	static std::string yamlType("lhc-sampler");
	const std::string& LhcSampler::YamlType()
	{
		return yamlType;
	}

	bool LhcSampler::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "count")
			parser.ReadScalar(m_noSamples);
		else
			return Sampler::ProcessYamlScalar(parser, context);

		return true;
	}

	void LhcSampler::FinishDeserialization()
	{
		m_places = new int[m_noSamples*m_dimension];
	}
  */
}

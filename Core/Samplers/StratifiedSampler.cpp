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

#include "StratifiedSampler.h"
#include "../Math.h"

namespace Hrt
{

	StratifiedSampler::StratifiedSampler(int dimension, int divNumber)
		: Sampler(dimension), 
		m_divNumber(divNumber)
	{
		Initialize();
	}

	StratifiedSampler::StratifiedSampler()
		: m_divNumber(0)
	{

	}

	StratifiedSampler::~StratifiedSampler()
	{
		delete [] m_positions;
		m_positions = NULL;
	}

	int StratifiedSampler::GetCount() 
	{ 
		return (int)Math::Pow(m_divNumber, (number)m_dimension); 
	}

	void StratifiedSampler::Shuffle()
	{
		for(int i=0; i<m_dimension; i++)
			m_positions[i] = i ==0 ? -1 : 0;
	}

	bool StratifiedSampler::NextSample(number *sample, RandomizerPtr randomizer)
	{
		int i=0;
		while (i < m_dimension)
		{
			if ( ++(m_positions[i]) < m_divNumber )
			{
				i = -1;
				break;
			}
			else
				m_positions[i] = 0;

			i++;
		}

		if (i == m_dimension)
			return false;

		for(i=0; i<m_dimension; i++)
			sample[i] = m_positions[i]*m_recipDivNumber + randomizer->RandomEndOpen(0, m_recipDivNumber);

		return true;
	}

	void StratifiedSampler::Initialize()
	{
		m_positions = new int[m_dimension];
		m_recipDivNumber = (number)(1.0/m_divNumber);
		Shuffle();
	}

	static std::string yamlType("stratified-sampler");
	const std::string& StratifiedSampler::YamlType()
	{
		return yamlType;
	}

	bool StratifiedSampler::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "strata-count")
			parser.ReadScalar(m_divNumber);
		else
			return Sampler::ProcessYamlScalar(parser, context);

		return true;
	}

	void StratifiedSampler::FinishDeserialization()
	{
		Initialize();
	}
}

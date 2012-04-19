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
#include "../Sampler.h"
#include "../Random.h"

namespace Hrt
{
	/// Sampler that generates random samples in range [0,1).
	class RandomSampler : public Sampler
	{
	public:
		RandomSampler();

		RandomSampler(int dimension, int noSamples);
		
		virtual void Shuffle(RandomizerPtr randomizer);

		virtual bool NextSample(number *sample, RandomizerPtr randomizer);

		virtual int GetCount() { return m_noSamples; }

		virtual SamplerOwnedPtr Clone() { return SamplerOwnedPtr(new RandomSampler(m_dimension, m_noSamples)); }

		virtual const std::string& YamlType();
		virtual bool ProcessYamlScalar(YamlParser& parser, SerializationContext& context );
		
	private:
		int m_noSamples;
		int m_currentSample;
	};

}

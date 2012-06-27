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
#pragma once
#include "../Common.h"
#include "../Sampler.h"
#include "../Random.h"

namespace Hrt
{
	/// Simple jittered stratified sampler.
	class StratifiedSampler : public Sampler
	{
	public:
		StratifiedSampler();
		StratifiedSampler(int dimension, int divNumber);

		virtual ~StratifiedSampler();

		virtual void Shuffle(RandomizerPtr randomizer) { Shuffle(); }

		virtual bool NextSample(number *sample, RandomizerPtr randomizer);

		virtual int GetCount();

		virtual SamplerOwnedPtr Clone() { return SamplerOwnedPtr(new StratifiedSampler(m_dimension, m_divNumber)); }

	private:
		int m_divNumber;
		int* m_positions;
		number m_recipDivNumber;

		void Initialize();
		void Shuffle();
	};

}

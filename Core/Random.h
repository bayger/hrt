#include "External\MersenneTwister.h"
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

namespace Hrt
{
	class Randomizer
	{
	public:
		/// Generates random number in closed range [minValue, maxValue].
		inline number Random(number minValue, number maxValue)
		{
			return (number)(minValue+rand.rand(maxValue-minValue));
		}

		/// Generates random number in range [minValue, maxValue).
		inline number RandomEndOpen(number minValue, number maxValue)
		{
			return (number)(minValue+rand.randExc(maxValue-minValue));
		}

		/// Generates random number in open range (minValue, maxValue).
		inline number RandomOpen(number minValue, number maxValue)
		{
			return (number)(minValue+rand.randDblExc(maxValue-minValue));
		}

		/// Generates 32-bit random integer in range [0,max].
		inline int Random(int max)
		{
			return rand.randInt(max);
		}

	private:
		MTRand rand;
	};

	class Randomizer;
	typedef shared_ptr<Randomizer> RandomizerOwnedPtr;
	typedef const RandomizerOwnedPtr& RandomizerPtr;
}
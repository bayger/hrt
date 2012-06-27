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
#include "Common.h"
#include "Random.h"

namespace Hrt
{
	/// Base class for all samplers used in Hrt.
	class Sampler
	{
	public:
		/// Creates not-initialized sampler.
		Sampler();

		/// Creates a sampler that generates samples with given dimension.
		/// \param dimension Dimension of generated samples
		Sampler(int dimension);

		/// Destroys sampler and releases all its resources.
		virtual ~Sampler(void);

		/// Fills sample array with a new sample and returns TRUE or returns
		/// FALSE if no more samples.
		/// \param sample Place for generated sample - it MUST be at least
		/// as big as dimension of generated sample (see constructor).
		/// \return Returns true for success or false when no more samples
		/// can be generated in current sampling batch.
		virtual bool NextSample(number *sample, RandomizerPtr randomizer)=0;

		/// Resets sampler (shuffle samples) so it can generate a new batch of samples.
		virtual void Shuffle(RandomizerPtr randomizer)=0;

		/// Returns dimension of generated samples.
		int GetDimension() const { return m_dimension; }

		/// Gets the number of samples per shuffle.
		virtual int GetCount()=0;

		/// Makes a clean clone of self.
		virtual shared_ptr<Sampler> Clone()=0;

	protected:
		int m_dimension;
	};

	/// Reference to const shared-pointer of Sampler (used as params and returns)
	typedef const shared_ptr<Sampler>& SamplerPtr;
	
	/// Shared-pointer of Sampler (version for owners)
	typedef shared_ptr<Sampler> SamplerOwnedPtr;
}

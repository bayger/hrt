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

namespace Hrt
{
	/// Dummy sampler - always generates 0.5
	class ConstSampler : public Sampler
	{
	public:
		ConstSampler();

		ConstSampler(int dimension);

		virtual ~ConstSampler(void);

		virtual bool NextSample(number *sample, RandomizerPtr randomizer);

		virtual void Shuffle(RandomizerPtr randomizer);

		virtual int GetCount() { return 1; }

		virtual SamplerOwnedPtr Clone() { return SamplerOwnedPtr(new ConstSampler(m_dimension)); }

		virtual const std::string& YamlType();
		virtual bool ProcessYamlScalar(YamlParser& parser, SerializationContext& context );

	private:
		bool m_isReset;
	};

}

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
#include "SamplerSerializer.h"
#include "../Serialization/YamlParser.h"
#include "../Serialization/SerializationContext.h"
#include "ConstSampler.h"
#include "LhcSampler.h"
#include "RandomSampler.h"
#include "StratifiedSampler.h"

namespace Hrt
{
	shared_ptr<Sampler> SamplerSerializer::Deserialize( std::string exactType,
		YamlParser& parser, SerializationContext& context )
	{
		if (exactType == "const-sampler")
		{
			SamplerOwnedPtr sampler(new ConstSampler());
			sampler->Deserialize(parser, context);
			return sampler;
		}
		else if (exactType == "lhc-sampler")
		{
			SamplerOwnedPtr sampler(new LhcSampler());
			sampler->Deserialize(parser, context);
			return sampler;
		}
		else if (exactType == "random-sampler")
		{
			SamplerOwnedPtr sampler(new RandomSampler());
			sampler->Deserialize(parser, context);
			return sampler;
		}
		else if (exactType == "stratified-sampler")
		{
			SamplerOwnedPtr sampler(new StratifiedSampler());
			sampler->Deserialize(parser, context);
			return sampler;
		}

		// add serialization support for other Samplers here
		// else if (exactType == "yaml-type-name") { ... }

		throw NotSupportedException("Sampler type not supported");
	}
}

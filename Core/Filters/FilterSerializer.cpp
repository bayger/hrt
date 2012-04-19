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
#include "stdafx.h"
#include "FilterSerializer.h"
#include "BoxFilter.h"
#include "GaussianFilter.h"
#include "SincFilter.h"
#include "TriangleFilter.h"
#include "../Serialization/YamlParser.h"
#include "../Serialization/SerializationContext.h"

namespace Hrt
{
	shared_ptr<Filter> FilterSerializer::Deserialize( std::string exactType,
		YamlParser& parser, SerializationContext& context )
	{
		if (exactType == "box-filter")
		{
			BoxFilter* bf;
			FilterOwnedPtr filter(bf = new BoxFilter());
			bf->Deserialize(parser, context);
			return filter;
		}
		else if (exactType == "gaussian-filter")
		{
			FilterOwnedPtr filter(new GaussianFilter());
			filter->Deserialize(parser, context);
			return filter;
		}
		else if (exactType == "sinc-filter")
		{
			FilterOwnedPtr filter(new SincFilter());
			filter->Deserialize(parser, context);
			return filter;
		}
		else if (exactType == "triangle-filter")
		{
			FilterOwnedPtr filter(new TriangleFilter());
			filter->Deserialize(parser, context);
			return filter;
		}

		// add serialization support for other filters here
		// else if (exactType == "yaml-type-name") { ... }

		throw NotSupportedException("Filter type not supported");
	}
}

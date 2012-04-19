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
#include "LightSerializer.h"
#include "PointLight.h"
#include "AreaLight.h"

namespace Hrt
{
	shared_ptr<Light> LightSerializer::Deserialize( std::string exactType, 
		YamlParser& parser, SerializationContext& context )
	{
		if (exactType == "point-light")
		{
			LightOwnedPtr light(new PointLight());
			light->Deserialize(parser, context);
			return light;
		}
		else if (exactType == "area-light")
		{
			LightOwnedPtr light(new AreaLight());
			light->Deserialize(parser, context);
			return light;
		}

		// add serialization support for other Lights here
		// else if (exactType == "yaml-type-name") { ... }

		throw NotSupportedException("Light type not supported");
	}
}

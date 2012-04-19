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
#include "MaterialSerializer.h"
#include "ASPhong.h"
#include "SimpleHe.h"
#include "Phong.h"
#include "CookTorrance.h"
#include "Ward.h"
#include "Mirror.h"

namespace Hrt
{
	shared_ptr<Material> MaterialSerializer::Deserialize( std::string exactType, 
		YamlParser& parser, SerializationContext& context )
	{
		if (exactType == "as-phong")
		{
			MaterialOwnedPtr material(new ASPhong());
			material->Deserialize(parser, context);
			return material;
		}
		else if (exactType == "phong")
		{
			MaterialOwnedPtr material(new Phong());
			material->Deserialize(parser, context);
			return material;
		}
		else if (exactType == "cook-torrance")
		{
			MaterialOwnedPtr material(new CookTorrance());
			material->Deserialize(parser, context);
			return material;
		}
		else if (exactType == "ward")
		{
			MaterialOwnedPtr material(new Ward());
			material->Deserialize(parser, context);
			return material;
		}
		else if (exactType == "htsg")
		{
			MaterialOwnedPtr material(new SimpleHe());
			material->Deserialize(parser, context);
			return material;
		}
		else if (exactType == "mirror")
		{
			MaterialOwnedPtr material(new Mirror());
			material->Deserialize(parser, context);
			return material;
		}

		// add serialization support for other materials here
		// else if (exactType == "yaml-type-name") { ... }

		throw NotSupportedException("Material type not supported");
	}
}

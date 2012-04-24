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
#include "../Common.h"
#include "ShapeSerializer.h"
#include "Cylinder.h"
#include "Disc.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"

namespace Hrt
{
	shared_ptr<Shape> ShapeSerializer::Deserialize( std::string exactType, 
		YamlParser& parser, SerializationContext& context )
	{
		if (exactType == "cylinder")
		{
			ShapeOwnedPtr shape(new Cylinder());
			shape->Deserialize(parser, context);
			return shape;
		}
		else if (exactType == "disc")
		{
			ShapeOwnedPtr shape(new Disc());
			shape->Deserialize(parser, context);
			return shape;
		}
		else if (exactType == "plane")
		{
			ShapeOwnedPtr shape(new Plane());
			shape->Deserialize(parser, context);
			return shape;
		}
		else if (exactType == "sphere")
		{
			ShapeOwnedPtr shape(new Sphere());
			shape->Deserialize(parser, context);
			return shape;
		}
		else if (exactType == "triangle")
		{
			ShapeOwnedPtr shape(new Triangle());
			shape->Deserialize(parser, context);
			return shape;
		}

		// add serialization support for other shapes here
		// else if (exactType == "yaml-type-name") { ... }

		throw NotSupportedException("Shape type not supported");
	}
}

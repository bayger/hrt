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
#include "../Shape.h"
#include "../Serialization/TypeSerializer.h"

namespace Hrt
{

	class ShapeSerializer
		: public TypeSerializer<Shape>
	{
	public:
		virtual shared_ptr<Shape> Deserialize(std::string exactType,
			YamlParser& parser, SerializationContext& context);
	};

}

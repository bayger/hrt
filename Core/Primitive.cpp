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
#include "Primitive.h"

namespace Hrt
{

	Primitive::Primitive(ShapePtr shape, MaterialPtr material)
		: m_shape(shape), m_material(material)
	{
	}

	Primitive::Primitive()
	{
	}

	bool Primitive::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "shape-name")
			parser.ReadScalar(m_shapeName);
		else if (scalarValue == "material-name")
			parser.ReadScalar(m_materialName);
		else
			return NamedObject::ProcessYamlScalar(parser, context);

		return true;
	}

	void Primitive::Initialize( ShapePtr shape, MaterialPtr material )
	{
		m_shape = shape;
		m_material = material;
		m_shapeName = shape->GetName();
		m_materialName = material->GetName();
	}

	static std::string yamlType("primitive");
	const std::string& Primitive::YamlType()
	{
		return yamlType;
	}
}

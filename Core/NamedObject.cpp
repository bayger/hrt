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
#include "NamedObject.h"

namespace Hrt
{

	bool NamedObject::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "name")
		{
			parser.ReadScalar(m_name);
		}
		else
			return false;

		return true;

	}

	static unsigned int oid = 1;
	void NamedObject::StartDeserialization()
	{
		m_name = str(format("%1%-oid-%2%") % YamlType() % oid);
		oid++;
	}
}

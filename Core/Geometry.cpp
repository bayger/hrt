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
#include "Geometry.h"

namespace Hrt
{

	Geometry::Geometry()
		: m_altered(false)
	{
	}

	Geometry::~Geometry()
	{
	}

	PrimitivePtr Geometry::operator [](uint index)
	{
		assert(index >= 0 && index < m_primitives.size());

		return m_primitives[index];
	}

	void Geometry::AddPrimitive(PrimitivePtr primitive)
	{
		m_altered = true;
		m_primitives.push_back(primitive);
	}

	void Geometry::RemovePrimitive(PrimitivePtr primitive)
	{
		std::vector< PrimitiveOwnedPtr >::iterator it = m_primitives.begin();
		std::vector< PrimitiveOwnedPtr >::iterator match = find(m_primitives.begin(), m_primitives.end(), primitive);

		if (match != m_primitives.end())
		{
			m_primitives.erase(match);
			m_altered = true;
		}
	}

	void Geometry::Clear()
	{
		m_primitives.clear();
	}

	uint Geometry::GetPrimitiveCount()
	{
		return (uint)m_primitives.size();
	}
}

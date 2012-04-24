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
#pragma once
#include "Common.h"
#include "Serialization/IYamlSerializable.h"

namespace Hrt
{
	/// Abstract class for 2D image reconstruction filters.
	/// \remark See Filters/ subdirectory for specific filters.
	class Filter
		: public IYamlSerializable
	{
	public:
		Filter(int width, int height);
		virtual ~Filter();

		/// Gets the horizontal range of a filter.
		int GetWidth() const { return m_width; }

		/// Gets the vertical range of a filter.
		int GetHeight() const { return m_height; }

		/// Calculates weight for given coordinates.
		/// \param x X-coordinate relative to filter center
		/// \param y Y-coordinate relative to filter center
		virtual number Calculate(number x, number y)=0;

		// IYamlSerializable Implementation
		virtual bool ProcessYamlScalar(YamlParser& parser, SerializationContext& context);

	protected:
		int m_width;
		int m_height;
	};

	/// Reference to const shared-pointer of Filter (used as params and returns)
	typedef const shared_ptr<Filter>& FilterPtr;
	
	/// Shared-pointer of Filter (version for owners)
	typedef shared_ptr<Filter> FilterOwnedPtr;
}

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
#include "Common.h"

namespace Hrt
{
	struct CieXyz;

	/// Class for storing HDR images.
	class Image
	{
	public:
		Image(uint width, uint height);
		~Image();

		/// Gets the encapsulated array of CIEXYZ pixels.
		inline CieXyz* GetPixels() const { return m_pixels; }

		/// Gets the width of the image.
		inline uint GetWidth() const { return m_width; }

		/// Gets the height of the image.
		inline uint GetHeight() const { return m_height; }

	private:
		CieXyz* m_pixels;
		uint m_width;
		uint m_height;
	};

	/// Reference to const shared-pointer of Image (used as params and returns)
	typedef const shared_ptr<Image>& ImagePtr;
	
	/// Shared-pointer of Image (version for owners)
	typedef shared_ptr<Image> ImageOwnedPtr;

}

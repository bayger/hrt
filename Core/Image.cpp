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
#include "Image.h"
#include "Rgba.h"

namespace Hrt
{

	Image::Image(uint width, uint height)
		: m_width(width), 
		m_height(height),
		m_pixels(new CieXyz[width*height])
	{}

	Image::~Image()
	{
		delete [] m_pixels;
		m_pixels = NULL;
		m_width = m_height = 0;
	}

}

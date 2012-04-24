/*
H-RT Toolkit - toolkit library for H-RayTracer ray tracing renderer.
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
#include "../Core/Common.h"
#include "../Core/Image.h"

using namespace Hrt;

namespace Hrt { namespace Tools
{
	/// Base class for all image codecs.
	class ImageCodec
	{
	public:
		ImageCodec(void) {}
		virtual ~ImageCodec(void) {}

		virtual ImageOwnedPtr LoadImage(const std::string& fileName)=0;

		virtual void SaveImage(ImagePtr image, const std::string& fileName)=0;
	};	

} }


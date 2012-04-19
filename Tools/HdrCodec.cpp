/*
H-RT Toolkit - toolkit library for H-RayTracer ray tracing renderer.
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
#include "../Core/Exceptions.h"
#include "../Core/Rgba.h"
#include "HdrCodec.h"

namespace Hrt { namespace Tools
{

	HdrCodec::HdrCodec()
	{
		FreeImage_Initialise();
	}

	ImageOwnedPtr HdrCodec::LoadImage(const std::string& fileName)
	{
		throw Hrt::NotImplementedException();
	}

	void HdrCodec::SaveImage(Hrt::ImagePtr image, const std::string& fileName)
	{
		CieXyz* pixels = image->GetPixels();

		FIBITMAP* bitmap = FreeImage_AllocateT(FIT_RGBF, image->GetWidth(), image->GetHeight());
		int i = 0;
		for(uint y=0; y<image->GetHeight(); y++)
		{
			float* scanline = (float*)FreeImage_GetScanLine(bitmap, y);
			for(uint x=0; x<image->GetWidth(); x++)
			{
				Rgb color;
				color.FromCieXyz(pixels[i]);
				
				scanline[x*3 + 0] = (float)color.R;
				scanline[x*3 + 1] = (float)color.G;
				scanline[x*3 + 2] = (float)color.B;

				i++;
			}
		}

		FreeImage_Save(FIF_HDR, bitmap, fileName.c_str());
		FreeImage_Unload(bitmap);
	}

} }

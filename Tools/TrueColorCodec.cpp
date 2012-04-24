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
#include "stdafx.h"
#include "TrueColorCodec.h"

namespace Hrt { namespace Tools
{
	TrueColorImageFormat::Enum GetFormatFromFileName(std::string fileName);

	TrueColorCodec::TrueColorCodec(
		TrueColorImageFormat::Enum fileFormat /* = TrueColorImageFormat::Unspecified */, 
		ToneMappingOperator::Enum toneMappingOperator /* = ToneMappingOperator::AdaptiveLogarithmic */)
		: m_format(fileFormat),
		m_tmOperator(toneMappingOperator)
	{
	}

	ImageOwnedPtr TrueColorCodec::LoadImage(const std::string &fileName)
	{
		throw NotImplementedException();
	}

	void TrueColorCodec::SaveImage(Hrt::ImagePtr image, const std::string &fileName)
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

		FIBITMAP* trueColorBitmap = FreeImage_ToneMapping(bitmap, (FREE_IMAGE_TMO)m_tmOperator);

		TrueColorImageFormat::Enum format = m_format;
		if (format == TrueColorImageFormat::Unspecified)
			format = GetFormatFromFileName(fileName);

		FreeImage_Save((FREE_IMAGE_FORMAT)format, trueColorBitmap, fileName.c_str());
		FreeImage_Unload(trueColorBitmap);
		FreeImage_Unload(bitmap);
	}

	/// Returns file format based on the file name (extension)
	TrueColorImageFormat::Enum GetFormatFromFileName(std::string fileName)
	{
		std::string::size_type dotPos = fileName.find_last_of('.');
		if (dotPos != std::string::npos)
		{
			std::string ext = fileName.substr(dotPos);
			if (ext == ".png")
				return TrueColorImageFormat::Png;
			if (ext == ".tif" || ext == ".tiff")
				return TrueColorImageFormat::Tiff;
			if (ext == ".bmp")
				return TrueColorImageFormat::Bmp;
		}

		return TrueColorImageFormat::Unspecified;
	}

} }

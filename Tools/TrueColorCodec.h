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
#include "ImageCodec.h"

namespace Hrt { namespace Tools
{
	/// Supported file formats for true color images.
	namespace TrueColorImageFormat
	{
		enum Enum
		{
			Unspecified = 0,
			Png = FIF_PNG,
			Tiff = FIF_TIFF,
			Bmp = FIF_BMP
		};
	}

	/// Supported tone mapping operators.
	namespace ToneMappingOperator
	{
		enum Enum
		{
			AdaptiveLogarithmic,
			DynamicRangeReduction
		};
	}

	/// True-color image codec. Supports lossless image formats and tonemapping.
	class TrueColorCodec : public ImageCodec
	{
	public:
		TrueColorCodec(TrueColorImageFormat::Enum fileFormat = TrueColorImageFormat::Unspecified,
			ToneMappingOperator::Enum toneMappingOperator = ToneMappingOperator::DynamicRangeReduction);

		virtual ImageOwnedPtr LoadImage(const std::string& fileName);

		virtual void SaveImage(ImagePtr image, const std::string& fileName);

	private:
		TrueColorImageFormat::Enum m_format;
		ToneMappingOperator::Enum m_tmOperator;
	};

} }

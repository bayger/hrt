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
#include "Canvas.h"
#include "Rgba.h"
#include "RayLight.h"
#include "Filter.h"
#include "CieXyz.h"
#include "Filters/FilterSerializer.h"

namespace Hrt
{

	Canvas::Canvas(int width, int height, FilterPtr filter)
		: m_width(width),
		m_height(height),
		m_filter(filter),
		m_image(new CieXyz[width*height]),
		m_depths(new number[width*height]),
		m_weights(new number[width*height]),
		m_stencil(new unsigned char[width*height]),
		m_isStoringRays(false)
	{
	}

	Canvas::Canvas()
		: m_width(0),
		m_height(0),
		m_image(NULL),
		m_weights(NULL),
		m_isStoringRays(false)
	{
	}

	Canvas::~Canvas(void)
	{
	}

	void Canvas::Prepare()
	{
		unsigned char* stencil = m_stencil.get();
		for(unsigned int i=0; i<m_width*m_height; i++)
		{
			stencil[i] = 0;
			m_image[i].X = m_image[i].Y = m_image[i].Z = 0;
		}
	}

	void Canvas::CollectRay(number canvasX, number canvasY, const Spectrum& radiance,
		number depth)
	{
		lock_guard<mutex> syncLock(m_collectMutex);

		CollectRayInternal(canvasX, canvasY, radiance, depth);
	}

	void Canvas::CollectRayInternal(number canvasX, number canvasY, const Spectrum& radiance,
		number depth)
	{
		m_depths[((unsigned int)canvasY)*m_width + (unsigned int)canvasX] = depth;

		if (m_isStoringRays)
		{
			RayHit hit;
			hit.Intensity = radiance;
			hit.X = canvasX;
			hit.Y = canvasY;
			m_hits.push_back(hit);
		}
		else
		{

			// calc filter range
			int startX = (int)Math::Ceiling(canvasX-m_filter->GetWidth());
			int endX = (int)Math::Floor(canvasX+m_filter->GetWidth());
			int startY = (int)Math::Ceiling(canvasY-m_filter->GetHeight());
			int endY = (int)Math::Floor(canvasY+m_filter->GetHeight());

			if (startX < 0) startX = 0;
			if (endX >= (int)m_width) endX = m_width-1;
			if (startY < 0) startY = 0;
			if (endY >= (int)m_height) endY = m_height-1;

			// apply filtered samples
			for(int y=startY; y<=endY; y++)
			{
				for(int x=startX; x<=endX; x++)
				{
					int offset = y*m_width+x;
					number weight = m_filter->Calculate((number)x-canvasX, (number)y-canvasY);
					CieXyz xyz = radiance.ToCieXyz();
					m_image[offset] += (xyz * weight);
					m_weights[offset] += weight;
				}
			}

			//m_image[((unsigned int)canvasY)*m_width + (unsigned int)canvasX] += radiance.ToCieXyz();
			//++(m_weights[((unsigned int)canvasY)*m_width + (unsigned int)canvasX]);
		}
	}

	ImageOwnedPtr Canvas::GenerateImage()
	{
		assert(m_filter.get() != NULL);
		ImageOwnedPtr image(new Image(m_width, m_height));
		CieXyz* pixels = image->GetPixels();

		if (m_isStoringRays)
		{
			number* weights = m_weights;
			for(unsigned int i=0; i<m_width*m_height; i++)
				weights[i] = 0;

			for(size_t i=0; i<m_hits.size(); i++)
			{
				RayHit& hit = m_hits[i];
				
				// calc filter range
				int startX = (int)Math::Ceiling(hit.X-m_filter->GetWidth());
				int endX = (int)Math::Floor(hit.X+m_filter->GetWidth());
				int startY = (int)Math::Ceiling(hit.Y-m_filter->GetHeight());
				int endY = (int)Math::Floor(hit.Y+m_filter->GetHeight());

				if (startX < 0) startX = 0;
				if (endX >= 320) endX = 319;
				if (startY < 0) startY = 0;
				if (endY >= 240) endY = 239;

				// apply filtered samples
				for(int y=startY; y<=endY; y++)
				{
					for(int x=startX; x<=endX; x++)
					{
						int offset = y*m_width+x;
						number weight = m_filter->Calculate((number)x-hit.X, (number)y-hit.Y);
						pixels[offset] += (hit.Intensity.ToCieXyz() * weight);
						weights[offset] += weight;
					}
				}
			}
		}
		else
		{
			for(unsigned int i=0; i<m_width*m_height; i++)
				pixels[i] = m_image[i];
		}

		// normalize colors
		for(unsigned int i=0; i<m_width*m_height; i++)
			if (m_stencil[i] > 0)
				pixels[i] = CieXyz(1,0,1);
			else if (m_weights[i] > 0)
				pixels[i] *= (number)1./m_weights[i];

		return image;
	}

	void Canvas::SetStencilValue( unsigned int x, unsigned int y, unsigned char val )
	{
		m_stencil.get()[y*m_width + x] = val;
	}

	unsigned char Canvas::GetStencilValue( unsigned int x, unsigned int y )
	{
		return m_stencil.get()[y*m_width + x];
	}

	Hrt::number Canvas::GetDepthValue( unsigned int x, unsigned int y )
	{
		return m_depths.get()[y*m_width + x];
	}

	Hrt::CieXyz Canvas::GetImageValue( unsigned int x, unsigned int y )
	{
		unsigned int i = y*m_width + x;
		return m_image[i]* num(1./m_weights[i]);
	}

	void Canvas::SetImageValue( unsigned int x, unsigned int y, CieXyz val )
	{
		unsigned int i = y*m_width + x;
		m_image[i] = val;
		m_weights[i] = 1;
	}

	bool Canvas::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "width")
			parser.ReadScalar(m_width);
		else if (scalarValue == "height")
			parser.ReadScalar(m_height);
		else if (scalarValue == "filter")
		{
			std::string scalarType = parser.CurrentTag();
			m_filter = Singleton<FilterSerializer>::Instance().Deserialize(scalarType,
				parser, context);
		}
		else
			return false;

		return true;
	}

	static std::string yamlType("canvas");
	const std::string& Canvas::YamlType()
	{
		return yamlType;
	}

	void Canvas::FinishDeserialization()
	{
		if (m_width == 0 || m_height == 0)
			throw InvalidOperationException("Canvas can't have zero size.");

		m_image = new CieXyz[m_width*m_height];
		m_depths.reset(new number[m_width*m_height]);
		m_weights = new number[m_width*m_height];
		m_stencil.reset(new unsigned char[m_width*m_height]);
		Prepare();
	}

	void Canvas::CollectRays(const std::vector<CanvasRay>& rays)
	{
		lock_guard<mutex> syncLock(m_collectMutex);

		for(std::vector<CanvasRay>::const_iterator it = rays.begin(); it != rays.end(); it++)
		{
			CollectRayInternal(it->CanvasX, it->CanvasY, it->Radiance, it->Depth);
		}
		
	}
}

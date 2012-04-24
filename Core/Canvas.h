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
#include "Spectrum.h"
#include "Filter.h"
#include "Image.h"
#include "Serialization/IYamlSerializable.h"
#include <vector>

namespace Hrt
{
	struct Rgb;
	struct RayLight;

	struct CanvasRay
	{
		number CanvasX;
		number CanvasY;
		Spectrum Radiance;
		number Depth;

		CanvasRay(number canvasX, number canvasY, const Spectrum& radiance, number depth)
			: CanvasX(canvasX),
			CanvasY(canvasY),
			Radiance(radiance),
			Depth(depth) 
		{ }
	};

	/// This class holds HDR image data.
	class Canvas
		: public IYamlSerializable
	{
	public:
		/// Creates not-initialized canvas
		Canvas();

		/// Create canvas with given size.
		/// \param width Width of the image
		/// \param height Height of the image
		/// \param filter Filter used to reconstruct image from samples
		Canvas(int width, int height, FilterPtr filter);

		/// Destroys canvas.
		~Canvas(void);

		/// Prepares canvas for collecting rays.
		void Prepare();

		/// Returns width of the canvas.
		unsigned int GetWidth() const { return m_width; }

		/// Returns height of the canvas.
		unsigned int GetHeight() const { return m_height; }
		
		/// Generates an image from collected ray samples.
		/// \param image Place for generated image (array of CieXyz[Width x Height]).
		ImageOwnedPtr GenerateImage();

		/// Returns filter used in this canvas.
		Filter* GetFilter() const { return m_filter.get(); }

		/// Adds radiance to the canvas.
		void CollectRay(number canvasX, number canvasY, const Spectrum& radiance,
			number depth);

		/// Adds multiple rays to the canvas.
		void CollectRays(const std::vector<CanvasRay>& rays);

		/// Sets the value of the stencil buffer for the specified pixel.
		void SetStencilValue(unsigned int x, unsigned int y, unsigned char val);

		/// Gets the value of the stencil buffer for the specified pixel.
		unsigned char GetStencilValue(unsigned int x, unsigned int y);

		/// Gets the value of the depth buffer for the specified pixel.
		number GetDepthValue(unsigned int x, unsigned int y);

		/// Gets the color of the specified pixel.
		CieXyz GetImageValue(unsigned int x, unsigned int y);

		void SetImageValue(unsigned int x, unsigned int y, CieXyz val);

		/// Returns true if every collected ray is stored for future use.
		bool IsStoringRays() const { return m_isStoringRays; }

		/// Enables or disables storing of every collected ray.
		/// \remarks Enabling this feature will cause a huge memory consumption, because
		/// every ray may occupy up to 1KB of memory (spectral color). Rendering image 320x240
		/// with 16 samples per pixel will occupy more than 1 GB of RAM. Pro for enabling this
		/// feature is ability to generate the same image using different filters without
		/// need of re-raytracing the scene. However this is only usable in systems with
		/// a lot of memory (probably only 64-bit systems with far more than 4GB of RAM).
		void SetStoringRays(bool isStoringRays) { m_isStoringRays = isStoringRays; }


		// IYamlSerializable Implementation

		virtual bool ProcessYamlScalar( YamlParser& parser, SerializationContext& context );
		virtual const std::string& YamlType();
		virtual void FinishDeserialization();
		
	private:
		unsigned int m_width;
		unsigned int m_height;
		bool m_isStoringRays;
		CieXyz* m_image;
		scoped_array<number> m_depths;
		scoped_array<unsigned char> m_stencil;
		number* m_weights;
		FilterOwnedPtr m_filter;
		mutex m_collectMutex;

		struct RayHit
		{
			Spectrum Intensity;
			number X, Y;
		};

		std::vector<RayHit> m_hits;
		void CollectRayInternal(number canvasX, number canvasY, const Spectrum& radiance,
			number depth);
	};

	/// Reference to const shared-pointer of Canvas (used as params and returns)
	typedef const shared_ptr<Canvas>& CanvasPtr;
	
	/// Shared-pointer of Canvas (version for owners)
	typedef shared_ptr<Canvas> CanvasOwnedPtr;
}

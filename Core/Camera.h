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
#include "Matrix.h"
#include "Canvas.h"
#include "Sampler.h"

namespace Hrt
{
	class Matrix;
	struct Ray;

	/// Class that implements camera model for HRT.
	class Camera
	{
	public:
		Camera(void);
		~Camera(void);

		/// Calculates a ray coming from the camera using given parameters
		/// \param sample 2D vector with coordinates in pixel [0..1)
		/// \param ray [out] Place for a computed ray
		/// \param canvasX [out] Computed X coordinate on the canvas
		/// \param canvasY [out] Computed Y coordinate on the canvas
		/// \param baseX X coordinate of a pixel on the canvas
		/// \param baseY Y coordinate of a pixel on the canvas
		void ComputeRay(number* sample, Ray& ray, number& canvasX, number& canvasY,
			unsigned int baseX, unsigned int baseY);

		/// Gets camera matrix.
		Matrix GetMatrix() const { return m_matrix; }

		/// Sets camera matrix.
		void SetMatrix(Matrix val);

		/// Switches the camera to operate using a given canvas.
		void SetCanvas(CanvasPtr canvas);

		/// Gets field of view factor for the camera.
		number GetFov() const { return m_fov; }

		/// Sets field of view of the camera.
		void SetFov(number val);

	private:
		Matrix m_matrix;
		number m_fov;
		number m_d, m_hw, m_hh;
	};

	/// Reference to const shared-pointer of Camera (used as params and returns)
	typedef const shared_ptr<Camera>& CameraPtr;
	
	/// Shared-pointer of Camera (version for owners)
	typedef shared_ptr<Camera> CameraOwnedPtr;
}

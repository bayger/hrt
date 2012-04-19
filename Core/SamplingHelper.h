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
#include "Math.h"
#include "Vector3D.h"

namespace Hrt
{

	class SamplingHelper
	{
	public:

		/// Returns uniformly randomized direction vector calculated from 2D sample.
		/// \param sample Two numbers in range [0..1) that represent
		/// sample for computation
		/// \return Direction in hemisphere calculated from sample.
		static Vector3D SampleHemisphere(number* sample, number& pdfResult);

		/// Returns cosine-lobe shaped randomized direction vector calculated using given 2D sample.
		/// \param sample Two numbers in range [0..1) that represent
		/// sample for computation
		/// \return Direction in hemisphere calculated from sample.
		static Vector3D SampleHemisphereCosineLobe(number* sample, number& pdfResult);

		/// Returns a direction in hemisphere in given coordinates system
		/// defined by 3 base vectors.
		/// \param sample Two numbers in range [0..1) that represent sample
		/// for computation
		/// \param xAxis Base X unit vector
		/// \param yAxis Base Y unit vector
		/// \param zAxis Base Z unit vector
		/// \return Direction in hemisphere calculated from sample.
		static Vector3D SampleHemisphere(number* sample, const Vector3D& xAxis, 
			const Vector3D& yAxis, const Vector3D& zAxis, number& pdfResult);

		static Vector3D SampleHemisphereCosineLobe(number* sample, const Vector3D& xAxis, 
			const Vector3D& yAxis, const Vector3D& zAxis, number& pdfResult);

		static number GetPdfHemisphere(const Vector3D& n, const Vector3D& direction);

		static number GetPdfHemisphereCosineLobe(const Vector3D& n, const Vector3D& direction);

	};

}

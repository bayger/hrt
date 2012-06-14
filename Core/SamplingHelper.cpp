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
#include "stdafx.h"
#include "SamplingHelper.h"

namespace Hrt
{
	//
	// ---
	//

	Vector3D SamplingHelper::SampleHemisphere(number* sample, number& pdfResult)
	{
		pdfResult = 1 / Consts::TwoPi;
		return Vector3D::FromSpherical(Consts::TwoPi*sample[0], Consts::HalfPi*Math::Arcos(sample[1]));
	}

	Vector3D SamplingHelper::SampleHemisphere(number* sample, const Vector3D& xAxis, 
		const Vector3D& yAxis, const Vector3D& zAxis, number& pdfResult)
	{
		pdfResult = 1 / Consts::TwoPi;
		return Vector3D::FromSpherical(Consts::TwoPi*sample[0], Consts::HalfPi*Math::Arcos(sample[1]),
			xAxis, yAxis, zAxis);
	}

	Hrt::Vector3D SamplingHelper::SampleHemisphereCosineLobe(number* sample, number& pdfResult)
	{
		number yAngle = Math::Arcos(Math::Sqrt(sample[1]));
		pdfResult = Math::Cos(yAngle) / Consts::Pi;
		return Vector3D::FromSpherical(Consts::TwoPi*sample[0], yAngle);
	}

	Vector3D SamplingHelper::SampleHemisphereCosineLobe(number* sample, const Vector3D& xAxis, 
		const Vector3D& yAxis, const Vector3D& zAxis, number& pdfResult)
	{
		number yAngle = Math::Arcos(Math::Sqrt(sample[1]));
		pdfResult = Math::Cos(yAngle) / Consts::Pi;
		return Vector3D::FromSpherical(Consts::TwoPi*sample[0], yAngle, xAxis, yAxis, zAxis);
	}

	Hrt::number SamplingHelper::GetPdfHemisphereCosineLobe(const Vector3D& n, const Vector3D& direction)
	{
		number cos_nd = n.Dot(direction);
		return cos_nd < 0 ? 0 : cos_nd / Consts::Pi;
	}

	Hrt::number SamplingHelper::GetPdfHemisphere(const Vector3D& n, const Vector3D& direction)
	{
		return n.Dot(direction) < 0 ? 0 : 1 / Consts::TwoPi;
	}
}

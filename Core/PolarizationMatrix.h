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

namespace Hrt
{
	/// \brief Represents a polarization of light for a single wavelength
	struct PolarizationMatrix
	{
	public:
		complexNumber Jxx, Jyy;
		complexNumber Jxy, Jyx;

		PolarizationMatrix()
			: Jxx(1), Jyy(1), Jxy(0), Jyx(0)
		{}

		PolarizationMatrix(complexNumber jxx, complexNumber jyy, 
			complexNumber jxy, complexNumber jyx)
			: Jxx(jxx), Jyy(jyy), Jxy(jxy), Jyx(jyx)
		{}

		/// Transforms polarization matrix by a given angle (between planes of incidence).
		/// \param theta Angle between two planes of incidence
		PolarizationMatrix Transform(number theta)
		{
			number cos_theta = Math::Cos(theta);
			number sin_theta = Math::Sin(theta);

			complexNumber xx = cos_theta*Jxx + sin_theta*Jyx;
			complexNumber xy = cos_theta*Jxy + sin_theta*Jyy;
			complexNumber yx = -sin_theta*Jxx + cos_theta*Jyx;
			complexNumber yy = -sin_theta*Jxy + cos_theta*Jyy;

			PolarizationMatrix result;
			result.Jxx = xx*cos_theta + xy*sin_theta;
			result.Jxy = xx*-sin_theta + xy*cos_theta;
			result.Jyx = yx*cos_theta + yy*sin_theta;
			result.Jyy = yx*-sin_theta + yy*cos_theta;

			return result;
		}

		/// Transforms polarization matrix by a given angle (between planes of incidence).
		/// \param l1 Normal of 1st plane of incidence
		/// \param l2 Normal of 2nd plane of incidence
		PolarizationMatrix Transform(Vector3D l1, Vector3D l2)
		{
			return Transform(Math::Arcos(l1*l2));
		}
        
        /// Performs a weighted add operation.
        static void WeightedAdd(number weightA, const PolarizationMatrix& a,
                number weightB, const PolarizationMatrix& b, PolarizationMatrix& result)
        {
            number ta = weightA / weightA+weightB;
            number tb = weightB / weightA+weightB;
            result.Jxx = ta*a.Jxx + tb*b.Jxx;
            result.Jyy = ta*a.Jyy + tb*b.Jyy;
            result.Jxy = ta*a.Jxy + tb*b.Jxy;
            result.Jyx = ta*a.Jyx + tb*b.Jyx;
        }
	};
}

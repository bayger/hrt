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
#include "Common.h"
#include "Math.h"

namespace Hrt
{
	/// Represents a color in CIE XYZ color-space.
	struct CieXyz
	{
		number X;
		number Y;
		number Z;

		CieXyz(number x, number y, number z)
			: X(x), Y(y), Z(z) {}
		CieXyz() : X(0), Y(0), Z(0) {}

		bool IsBlack()
		{
			return X == 0 && Y == 0 && Z == 0;
		}

		number MinPart() { return (X+Y+Z)/3; }//Math::Min(X, Y, Z); }

		number MaxPart() { return (X+Y+Z)/3; }//Math::Max(X, Y, Z); }

		number Lumi() { return Y; }

		CieXyz operator+(CieXyz& val)
		{
			return CieXyz(X+val.X, Y+val.Y, Z+val.Z);
		}

		CieXyz operator-(CieXyz& val)
		{
			return CieXyz(X-val.X, Y-val.Y, Z-val.Z);
		}

		CieXyz& operator+=(const CieXyz& val)
		{
			X += val.X;
			Y += val.Y;
			Z += val.Z;

			return *this;
		}

		CieXyz& operator-=(const CieXyz& val)
		{
			X -= val.X;
			Y -= val.Y;
			Z -= val.Z;

			return *this;
		}

		CieXyz& operator*=(number mul)
		{
			X *= mul;
			Y *= mul;
			Z *= mul;

			return *this;
		}

		bool operator==(CieXyz& val)
		{
			return X==val.X && Y==val.Y && Z==val.Z;
		}

		bool operator!=(CieXyz& val)
		{
			return X!=val.X || Y!=val.Y || Z!=val.Z;
		}
	};

	CieXyz operator*(const CieXyz& val, number mul);
	CieXyz operator*(number mul, const CieXyz& val);

}

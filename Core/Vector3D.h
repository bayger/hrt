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
#include "Math.h"

namespace Hrt
{
	/// Holds information about point in 3D space. Provides methods
	/// for manipulating such points.
	class Vector3D
	{
	public:
		number X;
		number Y;
		number Z;

		Vector3D(void)
			: X(0), Y(0), Z(0) {}
		Vector3D(number x, number y, number z)
			: X(x), Y(y), Z(z) {}
            
        inline void Set(number x, number y, number z)
        {
            X = x;
            Y = y;
            Z = z;
        }

		// Operators:

		bool operator!=(const Vector3D& vec) const
		{
			return X != vec.X || Y != vec.Y || Z != vec.Z;
		}

		bool operator==(const Vector3D& vec) const
		{
			return X == vec.X && Y == vec.Y && Z == vec.Z;
		}

		Vector3D operator+(const Vector3D& val) const
		{
			return Vector3D(X+val.X, Y+val.Y, Z+val.Z);
		}

		Vector3D operator-() const
		{
			return Vector3D(-X, -Y, -Z);
		}

		Vector3D& operator+=(Vector3D& val)
		{
			X += val.X;
			Y += val.Y;
			Z += val.Z;

			return *this;
		}

		Vector3D operator-(const Vector3D& val) const
		{
			return Vector3D(X-val.X, Y-val.Y, Z-val.Z);
		}

		Vector3D& operator-=(Vector3D& val)
		{
			X -= val.X;
			Y -= val.Y;
			Z -= val.Z;

			return *this;
		}

		Vector3D operator/(number val) const
		{
			number recip = 1/val;
			return Vector3D(X*recip, Y*recip, Z*recip);
		}

		Vector3D& operator/=(number val)
		{
			number recip = 1/val;
			X *= recip;
			Y *= recip;
			Z *= recip;
			return *this;
		}

		friend Vector3D operator*(number val, const Vector3D& vector);
		friend Vector3D operator*(const Vector3D& vector, number val);

		Vector3D& operator*=(number val)
		{
			X *= val;
			Y *= val;
			Z *= val;
			return *this;
		}

		inline bool IsUnit() const
		{
			return Math::Abs(1 - Length()) < epsilon;
		}

		inline bool AlmostEqualTo(Vector3D val) const
		{
			// TODO: base on relative error not absolute one
			return (Math::Abs( (*this - val).LengthSquared() ) < epsilon);
		}

		/// Returns normalized vector
		inline Vector3D Normalize() const
		{
			number len = (number)(1. / Length());
			return Vector3D(X*len, Y*len, Z*len);
		}

		/// Returns length of a vector
		inline number Length() const
		{
			return Math::Sqrt(X*X + Y*Y + Z*Z);
		}

		/// Returns squared length.
		inline number LengthSquared() const
		{
			return X*X + Y*Y + Z*Z;
		}

		/// Returns a dot product of 2 vectors
		inline number Dot(const Vector3D& val) const
		{
			return X*val.X + Y*val.Y + Z*val.Z;
		}

		/// Operator* version of a dot product
		inline number operator*(const Vector3D& val) const
		{
			return X*val.X + Y*val.Y + Z*val.Z;
		}

		/// Returns a cross product of 2 vectors
		inline Vector3D Cross(const Vector3D& val) const
		{
			return Vector3D(Y*val.Z-Z*val.Y, -(X*val.Z-Z*val.X), X*val.Y-Y*val.X);
		}

		/// Returns a reflected vector.
		/// \param by Reflection-axis vector.
		inline Vector3D Reflect(const Vector3D& by) const
		{
			number len = Dot(by);
			return len*2*by - *this;
		}

    inline bool IsNan() const
    {
      return Math::IsNan(X) || Math::IsNan(Y) || Math::IsNan(Z);
    }

		/// Transforms vector to another space.
		/// \param unitI Base unit vector I of destination space
		/// \param unitJ Base unit vector J of destination space
		/// \param unitK Base unit vector K of destination space
		/// \remarks Base unit vectors must be orthogonal
		Vector3D Transform(const Vector3D& unitI, 
			const Vector3D& unitJ, const Vector3D& unitK) const;

		static inline Vector3D FromSpherical(number azimuth, number elevation)
		{
			number cos_azimuth = Math::Cos(azimuth);
			number sin_azimuth = Math::Sin(azimuth);
			number cos_elevation = Math::Cos(elevation);
			number sin_elevation = Math::Sin(elevation);

			return Vector3D(sin_elevation * cos_azimuth,
				sin_elevation * sin_azimuth,
				cos_elevation);
		}

		static inline Vector3D FromSpherical(number azimuth, number elevation, const Vector3D& axisX, const Vector3D& axisY, const Vector3D& axisZ)
		{
			number cos_azimuth = Math::Cos(azimuth);
			number sin_azimuth = Math::Sin(azimuth);
			number cos_elevation = Math::Cos(elevation);
			number sin_elevation = Math::Sin(elevation);

			return axisX * (sin_elevation * cos_azimuth)
				+ axisY * (sin_elevation * sin_azimuth)
				+ axisZ * cos_elevation;
		}



		std::string ToString() const;

		static const Vector3D Zero;
		static const Vector3D UnitX;
		static const Vector3D UnitY;
		static const Vector3D UnitZ;
	};



}

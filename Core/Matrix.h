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

	class Vector3D;

	/// Matrix 4x4 class used in geometric transformations
	class Matrix
	{
	private:
		number		data[4][4]; 			///< Matrix data

	public:

		/// Default constructor creates an identity matrix
		Matrix();

		Matrix(number m11, number m12, number m13, number m14,
			number m21, number m22, number m23, number m24,
			number m31, number m32, number m33, number m34,
			number m41, number m42, number m43, number m44)
		{
			data[0][0] = m11; data[0][1] = m12; data[0][2] = m13; data[0][3] = m14;
			data[1][0] = m21; data[1][1] = m22; data[1][2] = m23; data[1][3] = m24;
			data[2][0] = m31; data[2][1] = m32; data[2][2] = m33; data[2][3] = m34;
			data[3][0] = m41; data[3][1] = m42; data[3][2] = m43; data[3][3] = m44;
		}

		/// Copy constructor
		Matrix(const Matrix& m);

		/// Makes an identity matrix
		void Identity();

		/// Fills matrix with zeros
		void Clear();

		/// Calculates determinant
		number CalculateDeterminant() const;

		/// Makes a fast matrix inverse
		void InverseFast();

		/// Transposes matrix so m'(i,j) = m(j,i)
		void Transpose();

		/// Multiplication of two matrices.
		Matrix operator*( const Matrix& mtx );

		/// Returns i-th row of matrix
		number operator()( int row, int col ) const;

		/// Returns true if two matrices are equal
		bool operator==( const Matrix& mtx ) const;

		/// Returns true if two matrices are NOT equal
		bool operator!=( const Matrix& mtx ) const;

		/// Checks if matrix is identity matrix
		bool IsIdentity() const;

		/// Creates translation matrix.
		static Matrix MakeTranslation( number x, number y, number z );

		/// Creates scale matrix.
		static Matrix MakeScale( number sx, number sy, number sz );

		/// Creates rotation matrix (YXZ)
		static Matrix MakeRotation( number h, number p, number b );

		/// Creates the projection matrix.
		static Matrix MakeProjection( number nearZ, number farZ, number zoomFactor );

		/// Applies the translation matrix.
		Matrix&	ApplyTranslation( number x, number y, number z );

		/// Applies scale matrix.
		Matrix&	ApplyScale( number sx, number sy, number sz );

		/// Applies rotation matrix.
		Matrix&	ApplyRotation( number h, number p, number b );

		Matrix& Matrix::MakeLookAt(const Vector3D& eye, const Vector3D& lookAt, const Vector3D& up);
		
	};

	/// Multiplies 3d vector by a matrix
	Vector3D operator*(const Vector3D& v, const Matrix& m );

}

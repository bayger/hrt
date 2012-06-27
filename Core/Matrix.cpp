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
#include "Exceptions.h"
#include "Matrix.h"
#include "Vector3D.h"
#include "Serialization/SerializationHelper.h"

namespace Hrt
{

	Matrix::Matrix()
	{
		Identity();
	}

	Matrix::Matrix(const Matrix& m)
	{
		for(char j=0; j<4; j++)
			for(char i=0; i<4; i++)
				data[j][i] = m.data[j][i];
	}

	void Matrix::Identity()
	{
		memset( data, 0, sizeof(data) );
		data[0][0] = data[1][1] = data[2][2] = data[3][3] = 1.0f;
	}

	void Matrix::Clear()
	{
		memset( data, 0, sizeof(data) );
	}

	number Matrix::CalculateDeterminant() const
	{
		// check if this matrix is correct
		if ( data[0][3] != 0 || data[1][3] != 0 || data[2][3] != 0 
			|| data[3][3] != 1 )
		{
			throw InvalidOperationException("Can't calculate determinant for this matrix");
		}

		return ( data[0][0] * (data[1][1] * data[2][2] - data[1][2] * data[2][1]) \
			-data[0][1] * (data[1][0] * data[2][2] - data[1][2] * data[2][0]) \
			+data[0][2] * (data[1][0] * data[2][1] - data[1][1] * data[2][0]) );

	}

	void Matrix::InverseFast()
	{
		number det;
		number rd;
		Matrix temp;

		det = CalculateDeterminant();
		if ( det < epsilon )
		{
			throw InvalidOperationException("Can't inverse this matrix - invalid determinant");
		}

		rd = (number)(1.0/CalculateDeterminant());

		// d(A)^T*1/detA
		temp.data[0][0] =  (data[1][1] * data[2][2] - data[1][2] * data[2][1]) * rd;
		temp.data[1][0] = -(data[1][0] * data[2][2] - data[1][2] * data[2][0]) * rd;
		temp.data[2][0] =  (data[1][0] * data[2][1] - data[1][1] * data[2][0]) * rd;
		temp.data[0][1] = -(data[0][1] * data[2][2] - data[0][2] * data[2][1]) * rd;
		temp.data[1][1] =  (data[0][0] * data[2][2] - data[0][2] * data[2][0]) * rd;
		temp.data[2][1] = -(data[0][0] * data[2][1] - data[0][1] * data[2][0]) * rd;
		temp.data[0][2] =  (data[0][1] * data[1][2] - data[0][2] * data[1][1]) * rd;
		temp.data[1][2] = -(data[0][0] * data[1][2] - data[0][2] * data[1][0]) * rd;
		temp.data[2][2] =  (data[0][0] * data[1][1] - data[0][1] * data[1][0]) * rd;

		temp.data[0][3] = temp.data[1][3] = temp.data[2][3] = 0.0f;
		temp.data[3][3] = 1.0f;

		temp.data[3][0] = -(data[3][0] * temp.data[0][0] + 
			data[3][1] * temp.data[1][0] + data[3][2] * temp.data[2][0]);
		temp.data[3][1] = -(data[3][0] * temp.data[0][1] + 
			data[3][1] * temp.data[1][1] + data[3][2] * temp.data[2][1]);
		temp.data[3][2] = -(data[3][0] * temp.data[0][2] + 
			data[3][1] * temp.data[1][2] + data[3][2] * temp.data[2][2]);

		*this = temp;
	}

	void Matrix::Transpose()
	{
		Matrix tmp;
		tmp = *this;

		data[1][0] = tmp.data[0][1];
		data[2][0] = tmp.data[0][2];
		data[3][0] = tmp.data[0][3];
		data[0][1] = tmp.data[1][0];
		data[2][1] = tmp.data[1][2];
		data[3][1] = tmp.data[1][3];
		data[0][2] = tmp.data[2][0];
		data[1][2] = tmp.data[2][1];
		data[3][2] = tmp.data[2][3];
		data[0][3] = tmp.data[3][0];
		data[1][3] = tmp.data[3][1];
		data[2][3] = tmp.data[3][2];
	}

	number Matrix::operator()( int row, int col ) const
	{
		return data[row][col];
	}

	bool Matrix::operator==( const Matrix& mtx ) const
	{
		return data[0][0] == mtx.data[0][0]
		&& data[1][0] == mtx.data[1][0]
		&& data[2][0] == mtx.data[2][0]
		&& data[3][0] == mtx.data[3][0]
		&& data[0][1] == mtx.data[0][1]
		&& data[1][1] == mtx.data[1][1]
		&& data[2][1] == mtx.data[2][1]
		&& data[3][1] == mtx.data[3][1]
		&& data[0][2] == mtx.data[0][2]
		&& data[1][2] == mtx.data[1][2]
		&& data[2][2] == mtx.data[2][2]
		&& data[3][2] == mtx.data[3][2]
		&& data[0][3] == mtx.data[0][3]
		&& data[1][3] == mtx.data[1][3]
		&& data[2][3] == mtx.data[2][3]
		&& data[3][3] == mtx.data[3][3];
	}

	bool Matrix::operator!=( const Matrix& mtx ) const
	{
		return data[0][0] != mtx.data[0][0]
		|| data[1][0] != mtx.data[1][0]
		|| data[2][0] != mtx.data[2][0]
		|| data[3][0] != mtx.data[3][0]
		|| data[0][1] != mtx.data[0][1]
		|| data[1][1] != mtx.data[1][1]
		|| data[2][1] != mtx.data[2][1]
		|| data[3][1] != mtx.data[3][1]
		|| data[0][2] != mtx.data[0][2]
		|| data[1][2] != mtx.data[1][2]
		|| data[2][2] != mtx.data[2][2]
		|| data[3][2] != mtx.data[3][2]
		|| data[0][3] != mtx.data[0][3]
		|| data[1][3] != mtx.data[1][3]
		|| data[2][3] != mtx.data[2][3]
		|| data[3][3] != mtx.data[3][3];
	}

	bool Matrix::IsIdentity() const
	{
		return 
			data[0][0] == 1 && data[0][1] == 0 && data[0][2] == 0 && data[0][3] == 0 &&
			data[1][0] == 0 && data[1][1] == 1 && data[1][2] == 0 && data[1][3] == 0 &&
			data[2][0] == 0 && data[2][1] == 0 && data[2][2] == 1 && data[2][3] == 0 &&
			data[3][0] == 0 && data[3][1] == 0 && data[3][2] == 0 && data[3][3] == 1;
	}


#define mtxMultiplyRow(row) \
	res.data[row][0] = mtx.data[0][0] * data[row][0] + mtx.data[1][0] * data[row][1] + mtx.data[2][0] * data[row][2] + mtx.data[3][0] * data[row][3]; \
	res.data[row][1] = mtx.data[0][1] * data[row][0] + mtx.data[1][1] * data[row][1] + mtx.data[2][1] * data[row][2] + mtx.data[3][1] * data[row][3]; \
	res.data[row][2] = mtx.data[0][2] * data[row][0] + mtx.data[1][2] * data[row][1] + mtx.data[2][2] * data[row][2] + mtx.data[3][2] * data[row][3]; \
	res.data[row][3] = mtx.data[0][3] * data[row][0] + mtx.data[1][3] * data[row][1] + mtx.data[2][3] * data[row][2] + mtx.data[3][3] * data[row][3];

	Matrix Matrix::operator*( const Matrix& mtx )
	{
		Matrix res;

		mtxMultiplyRow(0);
		mtxMultiplyRow(1);
		mtxMultiplyRow(2);
		mtxMultiplyRow(3);

		return res;
	}

#undef mtxMultiplyRow

	Matrix Matrix::MakeTranslation( number x, number y, number z )
	{
		Matrix m;
		m.data[3][0] = x;
		m.data[3][1] = y;
		m.data[3][2] = z;

		return m;
	}

	Matrix& Matrix::ApplyTranslation( number x, number y, number z )
	{
		char i;

		for(i=0;i<4;i++)
		{
			data[i][0] += x*data[i][3];
			data[i][1] += y*data[i][3];
			data[i][2] += z*data[i][3];
		}

		return *this;
	}

	Matrix Matrix::MakeScale( number sx, number sy, number sz )
	{
		Matrix m;
		m.data[0][0] = sx;
		m.data[1][1] = sy;
		m.data[2][2] = sz;

		return m;
	}

	Matrix& Matrix::ApplyScale( number sx, number sy, number sz )
	{
		data[0][0] *= sx;
		data[1][0] *= sx;
		data[2][0] *= sx;
		data[3][0] *= sx;
		data[0][1] *= sy;
		data[1][1] *= sy;
		data[2][1] *= sy;
		data[3][1] *= sy;
		data[0][2] *= sz;
		data[1][2] *= sz;
		data[2][2] *= sz;
		data[3][2] *= sz;

		return *this;
	}

	Matrix Matrix::MakeRotation( number h, number p, number b )
	{
		Matrix m;
		number sh,ch,sp,cp,sb,cb;

		sh = (number)sin(-h); ch = (number)cos(-h);
		sp = (number)sin(-p); cp = (number)cos(-p);
		sb = (number)sin(-b); cb = (number)cos(-b);

		// calculate rot. matrix
		m.data[0][0] = cb*ch - sb*sp*sh;
		m.data[0][1] = -sb*cp;
		m.data[0][2] = sh*cb + sb*sp*ch;
		m.data[1][0] = sb*ch + sp*cb*sh;
		m.data[1][1] = cb*cp;
		m.data[1][2] = sh*sb - sp*cb*ch;
		m.data[2][0] = -cp*sh;
		m.data[2][1] = sp;
		m.data[2][2] = cp*ch;
		m.data[3][0] = m.data[3][1] = m.data[3][2] = \
			m.data[0][3] = m.data[1][3] = m.data[2][3] = 0.0f;
		m.data[3][3] = 1.0;

		return m;
	}

	Matrix& Matrix::ApplyRotation( number h, number p, number b )
	{
		Matrix matrix = MakeRotation( h, p, b );
		*this = (*this) * matrix;

		return *this;
	}

	static void CalculateRotationAtAngles( Vector3D& eye, Vector3D& lookAt, float& h, float& p )
	{
		Vector3D a = lookAt - eye;
		a.Normalize();

		h = -((float)-atan2(a.X,-a.Z));
		p = -((float)asin(a.Y));
	}


	/** Creates rotation matrix from two points ('look-at' rotation matrix).
	\param	eye 	Source point
	\param	lookAt	Destination point
	\param	up	Up-orientation of the space
	\return Self reference.
	**/
	Matrix& Matrix::MakeLookAt(const Vector3D& eye, const Vector3D& lookAt, const Vector3D& up)
	{
		Vector3D un = up.Normalize();
		Vector3D zAxis = (lookAt - eye).Normalize();

		if ((1-abs(un.Dot(zAxis))) < epsilon) // in case up vector is the same as zAxis
			un.Set(un.Y, un.Z, un.X);

		Vector3D xAxis = up.Cross(zAxis).Normalize();
		Vector3D yAxis = zAxis.Cross(xAxis);

		data[0][3] = data[1][3] = data[2][3] = 0;

		data[0][0] = xAxis.X;	data[1][0] = yAxis.X; data[2][0] = zAxis.X;
		data[0][1] = xAxis.Y;	data[1][1] = yAxis.Y; data[2][1] = zAxis.Y;
		data[0][2] = xAxis.Z;	data[1][2] = yAxis.Z; data[2][2] = zAxis.Z;
		
		data[3][0] = eye.X;
		data[3][1] = eye.Y;
		data[3][2] = eye.Z;
		data[3][3] = 1;

		return *this;
	}

	Matrix Matrix::MakeProjection( number nearZ, number farZ, number zoomFactor )
	{
		Matrix m;
		number h,w,Q;

		m.Clear();

		if ( nearZ > farZ )
			throw InvalidArgumentException("Can't build projection matrix when nearZ > farZ");

		w = zoomFactor*(3.0f/4.0f);
		h = zoomFactor;
		if ( farZ == 1E300 )
			Q = 1;
		else
			Q = farZ/(farZ - nearZ);

		m.data[0][0] = w;
		m.data[1][1] = h;
		m.data[2][2] = Q;
		m.data[2][3] = 1.0f;
		m.data[3][2] = -Q*nearZ;

		return m;
	}

  /*
	bool Matrix::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "make-diagonal")
		{
			number val;
			parser.ReadScalar(val);
			Identity();
			data[0][0] = data[1][1] = data[2][2] = val;
		}
		else if (scalarValue == "look-at")
		{
			Vector3D vec = SerializationHelper::ReadVector3D(parser);
			Vector3D eye(data[3][0], data[3][1], data[3][2]);

			*this = MakeLookAt(eye, vec, Vector3D::UnitY);
		}
		else if (scalarValue == "fill")
		{
			number val;
			parser.ReadScalar(val);
			for(char j=0; j<4; j++)
				for(char i=0; i<4; i++)
					data[j][i] = val;
		}
		else if (scalarValue == "make-translation")
		{
			Vector3D vec = SerializationHelper::ReadVector3D(parser);
			*this = MakeTranslation(vec.X, vec.Y, vec.Z);
		}
		else if (scalarValue == "make-scale")
		{
			Vector3D vec = SerializationHelper::ReadVector3D(parser);
			*this = MakeScale(vec.X, vec.Y, vec.Z);
		}
		else if (scalarValue == "make-rotation")
		{
			Vector3D vec = SerializationHelper::ReadVector3D(parser);
			*this = MakeRotation(vec.X, vec.Y, vec.Z);
		}
		else if (scalarValue == "translate")
		{
			Vector3D vec = SerializationHelper::ReadVector3D(parser);
			ApplyTranslation(vec.X, vec.Y, vec.Z);
		}
		else if (scalarValue == "rotate")
		{
			Vector3D vec = SerializationHelper::ReadVector3D(parser);
			ApplyRotation(vec.X, vec.Y, vec.Z);
		}
		else if (scalarValue == "scale")
		{
			Vector3D vec = SerializationHelper::ReadVector3D(parser);
			ApplyScale(vec.X, vec.Y, vec.Z);
		}
		else if (scalarValue == "row-1")
		{
			Vector3D vec = SerializationHelper::ReadVector3D(parser);
			data[0][0] = vec.X;
			data[0][1] = vec.Y;
			data[0][2] = vec.Z;
		}
		else if (scalarValue == "row-2")
		{
			Vector3D vec = SerializationHelper::ReadVector3D(parser);
			data[1][0] = vec.X;
			data[1][1] = vec.Y;
			data[1][2] = vec.Z;
		}
		else if (scalarValue == "row-3")
		{
			Vector3D vec = SerializationHelper::ReadVector3D(parser);
			data[2][0] = vec.X;
			data[2][1] = vec.Y;
			data[2][2] = vec.Z;
		}
		else
			return false;

		return true;
	}

	static std::string yamlType("matrix");
	const std::string& Matrix::YamlType()
	{
		return yamlType;
	}
  */
	Vector3D operator*(const Vector3D& v, const Matrix& m )
	{
		return Vector3D(
			v.X * m(0,0) + v.Y * m(1,0) + v.Z * m(2,0) + m(3,0),
			v.X * m(0,1) + v.Y * m(1,1) + v.Z * m(2,1) + m(3,1),
			v.X * m(0,2) + v.Y * m(1,2) + v.Z * m(2,2) + m(3,2)
			);
	}

}

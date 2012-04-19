/*
 * H-RT Core - the core of the H-RayTracer ray tracing renderer.
 * Copyright (c) 2006-2010 H-RT Team.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include "stdafx.h"
#include "Vector3D.h"

namespace Hrt
{
    
    Vector3D operator*(number val, const Vector3D& vector)
    {
        return Vector3D(vector.X*val, vector.Y*val, vector.Z*val);
    }
    
    Vector3D operator*(const Vector3D& vector, number val)
    {
        return Vector3D(vector.X*val, vector.Y*val, vector.Z*val);
    }
    
    
    Vector3D Vector3D::Transform(const Vector3D& unitI,
            const Vector3D& unitJ, const Vector3D& unitK) const
    {
        return    Vector3D(X*unitI.X, X*unitJ.X, X*unitK.X)
                + Vector3D(Y*unitI.Y, Y*unitJ.Y, Y*unitK.Y)
                + Vector3D(Z*unitI.Z, Z*unitJ.Z, Z*unitK.Z);
    }

		std::string Vector3D::ToString() const
		{
			return str(format("(%1%,%2%,%3%)") % X % Y % Z);
		}

    const Vector3D Vector3D::Zero(0, 0, 0);
    const Vector3D Vector3D::UnitX(1, 0, 0);
    const Vector3D Vector3D::UnitY(0, 1, 0);
    const Vector3D Vector3D::UnitZ(0, 0, 1);
    
}

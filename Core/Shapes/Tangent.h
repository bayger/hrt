#pragma once

namespace Hrt
{

	inline void ComputeTangents(const Vector3D& n, Vector3D& u, Vector3D& v)
	{

		// plane: nX*x + nY*y + nZ*z = 0
		if (n.Y != 0)
			u = Vector3D(1, -n.X/n.Y, 0).Normalize();
		else if (n.X != 0)
			u = Vector3D(-n.Y/n.X, 1, 0).Normalize();
		else 
			u = Vector3D(1, 0, -n.X/n.Z).Normalize();

		v = n.Cross(u).Normalize();

		if (_isnan(u.X) || _isnan(v.X) || _isnan(n.X))
			std::cout << "NaN ";
	}

}
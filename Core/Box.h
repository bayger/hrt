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
#include "Ray.h"

namespace Hrt
{

	// Axis-aligned box used as bounding shape.
	class BoundingBox
	{
	public:
		BoundingBox()
			: m_min(Vector3D::Zero),
			m_max(Vector3D::Zero) {}

		BoundingBox(Vector3D& min, Vector3D& max)
			: m_min(min),
			m_max(max) {}

		BoundingBox(number minX, number minY, number minZ, number maxX, number maxY, number maxZ)
			: m_min(Vector3D(minX, minY, minZ)),
			m_max(Vector3D(maxX, maxY, maxZ)) {}

		/// Returns true if box has volume equal to 0.
		bool HasZeroVolume()
		{
			return m_min.X == m_max.X || m_min.Y == m_max.Y || m_min.Z == m_max.Z;
		}

		/// Returns the volume of the box.
		number GetVolume()
		{
			return (m_max.X - m_min.X) * (m_max.Y - m_min.Y) * (m_max.Z - m_min.Z);
		}

		/// Checks whether ray intersects this box.
		/// Some suggestions taken from http://www.cs.utah.edu/~awilliam/box/
		bool Intersect(const Ray& ray)
		{
			number rx = 1/ray.Direction.X;
			number txe = rx >= 0 ? (m_min.X-ray.Position.X)*rx : (m_max.X-ray.Position.X)*rx;
			number txl = rx >= 0 ? (m_max.X-ray.Position.X)*rx : (m_min.X-ray.Position.X)*rx;

			number ry = 1/ray.Direction.Y;
			number tye = ry >= 0 ? (m_min.Y-ray.Position.Y)*ry : (m_max.Y-ray.Position.Y)*ry;
			number tyl = ry >= 0 ? (m_max.Y-ray.Position.Y)*ry : (m_min.Y-ray.Position.Y)*ry;

			if (txe > tyl || tye > txl)
				return false;

			number te = txe < tye ? tye : txe;
			number tl = txl > tyl ? tyl : txl;

			number rz = 1/ray.Direction.Z;
			number tze = rz >= 0 ? (m_min.Z-ray.Position.Z)*rz : (m_max.Z-ray.Position.Z)*rz;
			number tzl = rz >= 0 ? (m_max.Z-ray.Position.Z)*rz : (m_min.Z-ray.Position.Z)*rz;

			return !(te > tzl || tl < tze);
		}

	private:
		Vector3D m_min;
		Vector3D m_max;
	};

}

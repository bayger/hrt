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
#include "Camera.h"
#include "Sampler.h"
#include "Exceptions.h"
#include "Canvas.h"
#include "Matrix.h"
#include "Ray.h"
#include "Math.h"

namespace Hrt
{
	Camera::Camera(void)
		: m_fov(Consts::HalfPi)
	{
	}

	Camera::~Camera(void)
	{
	}

	void Camera::SetCanvas(CanvasPtr canvas)
	{
		assert(canvas != NULL);

		m_hw = (number)(canvas->GetWidth()*0.5);
		m_hh = (number)(canvas->GetHeight()*0.5);
		m_d = (number)(Math::Ctg(m_fov/2)*m_hw);
	}

	void Camera::SetMatrix(Matrix val)
	{ 
		m_matrix = val; 
	}

	void Camera::SetFov(number val)
	{
		assert(val > 0);

		m_fov = val;
	}

	void Camera::ComputeRay( number* sample, Ray& ray, number& canvasX, number& canvasY,
		unsigned int baseX, unsigned int baseY)
	{
		assert(sample != 0);

		number dx = (number)(sample[0] - 0.5);
		number dy = (number)(sample[1] - 0.5);
		canvasX = baseX+dx;
		canvasY = baseY+dy;

		ray.Position = Vector3D(0,0,0) * m_matrix; // TODO: add proper method to Matrix
		ray.Direction = (Vector3D(canvasX-m_hw, canvasY-m_hh, m_d).Normalize() 
			* m_matrix - ray.Position);
	}

	bool Camera::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "transform")
		{
			m_matrix.Deserialize(parser, context);
		}
		else if (scalarValue == "fov")
		{
			parser.ReadScalar(m_fov);
		}
		else
			return false;

		return true;
	}

	static std::string yamlType("camera");
	const std::string& Camera::YamlType()
	{
		return yamlType;
	}
}

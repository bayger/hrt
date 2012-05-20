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

#include "SincFilter.h"
#include "../Math.h"

namespace Hrt
{

	number SincFilter::Calculate(Hrt::number x, Hrt::number y)
	{
		if (x < -m_width && x > m_width && y < -m_height && y > m_height)
			return 0;

		if (m_hasEnvelope)
			return Math::Sinc(Consts::Pi*x) * Math::Cos(x*m_xEnvelope)
				 * Math::Sinc(Consts::Pi*y) * Math::Cos(y*m_yEnvelope);
		else
			return Math::Sinc(Consts::Pi*x) * Math::Sinc(Consts::Pi*y);
	}

	static std::string yamlType("sinc-filter");
	const std::string& SincFilter::YamlType()
	{
		return yamlType;
	}

  void SincFilter::FinishDeserialization()
  {
    m_xEnvelope = Consts::HalfPi / m_width;
    m_yEnvelope = Consts::HalfPi / m_height;
  }

}

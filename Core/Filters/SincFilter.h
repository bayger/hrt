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
#include "../Common.h"
#include "../Math.h"
#include "../Filter.h"

namespace Hrt
{

	/// Sinc filter with optional sinus envelope.
	class SincFilter : public Filter
	{
	public:
		SincFilter()
			: Filter(1,1),
			m_hasEnvelope(false),
			m_xEnvelope(1),
			m_yEnvelope(1)
		{ }

		SincFilter(int width, int height, bool withEnvelope)
			: Filter(width, height),
			m_hasEnvelope(withEnvelope),
			m_xEnvelope(Consts::HalfPi/width),
			m_yEnvelope(Consts::HalfPi/height)
		{ }

		virtual number Calculate(number x, number y);

		virtual const std::string& YamlType();

	private:
		bool m_hasEnvelope;
		number m_xEnvelope;
		number m_yEnvelope;
	};

}

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
#include "Spectrum.h"
#include "Scene.h"
#include "Ray.h"

namespace Hrt
{
	/// Base class for radiance integrators.
	class RadianceIntegrator
	{
	public:
		virtual Spectrum CalculateRadiance(const shared_ptr<Scene>& scene, Ray& ray,
			int level, number cumulativeImportance) const =0;
	};

	/// Reference to const shared-pointer of RadianceIntegrator (used as params and returns)
	typedef const shared_ptr<RadianceIntegrator>& RadianceIntegratorPtr;
	
	/// Shared-pointer of RadianceIntegrator (version for owners)
	typedef shared_ptr<RadianceIntegrator> RadianceIntegratorOwnedPtr;
}

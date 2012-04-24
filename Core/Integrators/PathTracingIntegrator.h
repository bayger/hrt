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
#include "../Common.h"
#include "../RadianceIntegrator.h"
#include "../Scene.h"
#include "../Ray.h"
#include "../LightIntegrator.h"
#include <iostream>
#include <fstream>

namespace Hrt
{

	/// A path-tracing integrator. Version 1 in experimental phase
	class PathTracingIntegrator : public LightIntegrator
	{
	public:
		PathTracingIntegrator(int maxDepth, int minDepth, number alpha = -1);

		virtual ~PathTracingIntegrator();

		virtual void CalculateLight(const Ray& ray, Scene &scene, RayLight &result, unsigned int level, RenderingContext& rc) const;

		virtual int GetMaxLevels() const { return m_maxDepth; }

		int64 GetCalculationCount() const { return m_calculationCount; }

		int64 GetPathCount() const { return m_pathCount; }

	private:
		int m_maxDepth;
		int m_minDepth;
		number m_alpha;
		bool useAdaptiveRR;

		volatile mutable int64 m_calculationCount;
		volatile mutable int64 m_pathCount;
	};

}

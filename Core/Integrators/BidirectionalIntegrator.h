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
#include "../LightIntegrator.h"

namespace Hrt
{
	/// Vertex used in bidirectional path tracing
	struct BdptVertex
	{
		Vector3D Position;
		Spectrum Alpha;

		BdptVertex(const Vector3D& position, Spectrum alpha)
			: Position(position),
			Alpha(alpha)
		{ }
	};

	/// Bidirectional path-tracing integrator
	class BidirectionalIntegrator : public LightIntegrator
	{
		/// \param maxDepth This one actually defines maximal subpath length either from light or from eye.
		/// \param alpha Russian roulette rejection probability
		BidirectionalIntegrator(int maxDepth, number alpha);

		virtual void CalculateLight(const Ray& ray, Scene &scene, RayLight &result, unsigned int level, RenderingContext& rc) const;
		
		virtual int GetMaxLevels() const { return m_maxDepth; }

		void Prepare(ScenePtr scene);

	private:
		int m_maxDepth;
		number m_alpha;

		std::vector<number> lightWeights;
		std::vector<size_t> lightIndices;

		mutable std::vector<BdptVertex> lightSubpath;
		mutable std::vector<BdptVertex> eyeSubpath;
	};
}
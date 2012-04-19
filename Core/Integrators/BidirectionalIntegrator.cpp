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
#include "stdafx.h"
#include "BidirectionalIntegrator.h"

namespace Hrt
{
	size_t RandomizeLight(const std::vector<number>& power, const std::vector<size_t>& indices, number urv)
	{
		std::vector<number>::const_iterator match = std::lower_bound(power.begin(), power.end(), urv);
		size_t matchIndex = match - power.begin();

		return indices[matchIndex];
	}

	BidirectionalIntegrator::BidirectionalIntegrator(int maxDepth, number alpha)
		: m_maxDepth(maxDepth), 
		m_alpha(alpha)
	{
		lightSubpath.reserve(m_maxDepth);
		eyeSubpath.reserve(m_maxDepth);
	}

	static void RandomizeLightPath(LightPtr light, std::vector<BdptVertex>& pathVertices, Scene& scene)
	{

	}

	void BidirectionalIntegrator::CalculateLight(const Ray& ray, Scene &scene, RayLight &result, unsigned int level, 
		RenderingContext& rc) const
	{
		Spectrum alpha;
		Intersection is;
		GeometryPtr geometry = scene.GetGeometry();
		Ray r;

		// randomize light, position and direction
		size_t lightIndex = RandomizeLight(lightWeights, lightIndices, rc.GetRandomizer()->RandomEndOpen(0, 1));
		LightPtr light = scene.GetLight(lightIndex);
		number lightPdf = 0;
		RayLight rl;
		light->GenerateRayLight(&rl, lightPdf, rc);
		Spectrum lr = rl.Radiance;

		// randomize and calculate light subpath
		lightSubpath.clear();
		size_t s = 0;
		alpha = 1;
		r = rl;
		Spectrum f;
		number pdf = 1;
		Vector3D prevPos = rl.Position;
		while (s < m_maxDepth)
		{
			number q = (s == 0 ? 0 : m_alpha);
			if (rc.GetRandomizer()->RandomEndOpen(0, 1) < q)
				break;

			if (!geometry->Intersect(r, &is))
				break;

			MaterialPtr material = is.HitPrimitive->GetMaterial();

			if (material == 0) // we hit luminaire
				break;

			Vector3D direction = material->SampleVector(&rc.GetLevelSamples()[2*s], -r.Direction, is.TangentU, is.TangentV, 
				is.Normal, pdf);
			
			rl.Direction = -direction;
			rl.Radiance = 1;
			f = material->CalculateBsdf(rl, is);

			lightSubpath.push_back(BdptVertex(prevPos, alpha));
			
			alpha = s > 0 
				? alpha * f / (pdf * (1-q)) // *cos
				: lr / lightPdf; 
			prevPos = is.Position;
			r = rl;
			r.Direction = direction;

			s++;
		}

		// randomize and calculate eye subpath
		eyeSubpath.clear();
		size_t t = 0;
		alpha = 1;
		r = ray;
		prevPos = ray.Position;
		while (t < m_maxDepth)
		{
			number q = (t == 0 ? 0 : m_alpha);
			if (rc.GetRandomizer()->RandomEndOpen(0, 1) < q)
				break;

			if (!geometry->Intersect(r, &is))
				break;

			MaterialPtr material = is.HitPrimitive->GetMaterial();

			if (material == 0) // we hit luminaire
				break;

			Vector3D direction = material->SampleVector(&rc.GetLevelSamples()[2*s], -r.Direction, is.TangentU, is.TangentV, 
				is.Normal, pdf);

			rl.Direction = -direction;
			rl.Radiance = 1;
			f = material->CalculateBsdf(rl, is);

			lightSubpath.push_back(BdptVertex(prevPos, alpha));

			alpha = t > 0 
				? alpha * f / (pdf * (1-q)) // *cos
				: 1;
			prevPos = is.Position;
			r = rl;
			r.Direction = direction;

			t++;
		}

		// connect the dots ;)
		result.Radiance = 0;
		for(size_t l=0; l<s; l++)
		{
			const BdptVertex& vl = lightSubpath[l];
			for(size_t e=1; e<t; e++) // ignore 1st vertex
			{
				const BdptVertex& ve = eyeSubpath[e];
				bool g = l > 0 ? geometry->CheckVisibility(vl.Position, ve.Position) : true;
				if (!g)
					continue;

				Spectrum x;
				if (l == 0) // direct lighting
				{
					// ...
				}
				else
				{
					// ...
				}

				result.Radiance += vl.Alpha * x * ve.Alpha;
			}
		}

		result.Radiance /= s+t;
	}

	void BidirectionalIntegrator::Prepare(ScenePtr scene)
	{
		number power = 0;
		// count all power emitted by all lights (finite-power ones)
		for(size_t i=0; i<scene->GetLightCount(); i++)
		{
			LightPtr light = scene->GetLight(i);

			if (light->HasFinitePower())
			{
				power += scene->GetLight(i)->GetPower().GetAverage();
				lightWeights.push_back(power);
				lightIndices.push_back(i);
			}
		}

		if (power == 0)
			throw InvalidOperationException("The scene doesn't contain any finite-power lights");

		// normalize
		for(size_t i=0; i<lightWeights.size(); i++)
			lightWeights[i] /= power;
	}

}
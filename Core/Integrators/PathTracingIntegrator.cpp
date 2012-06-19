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

#include "PathTracingIntegrator.h"
#include "../Exceptions.h"
#include "../SamplingHelper.h"
#include "../Samplers/RandomSampler.h"
#include "../Samplers/StratifiedSampler.h"
#include "../LightEmitter.h"

namespace Hrt
{

	PathTracingIntegrator::PathTracingIntegrator(int maxDepth, int minDepth, number alpha)
		: m_maxDepth(maxDepth),
		m_minDepth(minDepth),
		m_alpha(alpha),
		m_calculationCount(0),
		m_pathCount(0),
		useAdaptiveRR(alpha < 0)
	{
	}

	PathTracingIntegrator::~PathTracingIntegrator()
	{
	}

	static Spectrum GetLightEmitterRadiance(shared_ptr<LightEmitter> lightEmitter, const Ray& r, const Intersection& intersection)
	{
		Spectrum radiance;
		Vector3D luminaireNormal;
		
		lightEmitter->CalculateRadiance(intersection.Position, luminaireNormal, radiance);

		return radiance * r.Direction.Dot(-luminaireNormal);
	}

	static number WeightByPowerHeuristic(number pdf1, number pdf2)
	{
		return (pdf1*pdf1) / (pdf1*pdf1 + pdf2*pdf2);
	}

	void PathTracingIntegrator::CalculateLight(const Ray& ray, Scene &scene, RayLight &result, unsigned int level, RenderingContext& rc) const
	{
		int depth = 0;
		GeometryPtr geometry = scene.GetGeometry();
		Ray incoming = ray;
		Intersection intersection;
		Spectrum r = 0;
		Spectrum throughput = 1;
		RayLight incident;

		while (depth < m_maxDepth)
		{
			number* samples = &(rc.GetLevelSamples()[depth*2]);

			if (throughput < epsilon)
				break;

			// 1. find intersection with nearest object
			if (!geometry->Intersect(incoming, &intersection))
				break;

			// we've hit a luminaire, so we can stop here (+ special case)
			if (intersection.HitPrimitive->GetShape()->IsLuminaire())
			{
				if (depth == 0)
				{
					r = GetLightEmitterRadiance(dynamic_pointer_cast<LightEmitter>(intersection.HitPrimitive->GetShape()), incoming, intersection);
					m_calculationCount++;
				}

				break;
			}

			MaterialPtr material = intersection.HitPrimitive->GetMaterial();

			number materialPdf;
      LightingType::Enum lightingType;
			Vector3D materialSampledVector = material->SampleVector(samples, -incoming.Direction, 
				intersection.TangentU, intersection.TangentV, intersection.Normal, materialPdf, lightingType);

			// 2. direct lighting (by all lights)
			for (uint i=0; i<scene.GetLightCount(); i++)
			{
				Spectrum sum = 0;
				int k = 0;
				LightOwnedPtr light = rc.GetLights()[i];// scene.GetLight(i);
				light->Prepare(intersection.Position, intersection.Normal, rc);
				bool isDelta = light->IsDeltaLight();

				number lightPdf;
				while(light->GenerateRayLight(&incident, lightPdf, rc))
				{
					if (geometry->CheckVisibility(incident.Position, intersection.Position))
					{
						Spectrum reflectedRadiance = material->CalculateRadiance(incident, intersection);
						number cos_in = intersection.Normal.Dot(-incident.Direction);

						if (cos_in <= 0)
							continue;

						if (isDelta)
							sum += reflectedRadiance * cos_in;
						else
						{

							// multiple importance sampling
							// a. light
							
							// convert material pdf to light area coordinates
							number mPdf = material->CalculatePdf(-incoming.Direction, intersection.TangentU, intersection.TangentV,
								intersection.Normal, incident.Direction, lightingType) 
                * Math::Abs(incident.Direction.Dot(incident.LightNormal))
								/ (intersection.Position-incident.Position).LengthSquared();
							number wl = WeightByPowerHeuristic(lightPdf, mPdf);

							sum += reflectedRadiance * cos_in * wl 
							 * Math::Abs(incident.Direction.Dot(incident.LightNormal))
							 / ((intersection.Position-incident.Position).LengthSquared() * lightPdf);

							// b. material

							Ray materialRay;
							materialRay.Direction = materialSampledVector;
							materialRay.Position = intersection.Position + epsilon*materialSampledVector;
							Intersection lightIntersection;
							
							if (geometry->Intersect(materialRay, &lightIntersection))
							{
								ShapeOwnedPtr shape = light->GetEmitterShape();
								if (lightIntersection.HitPrimitive->GetShape() == shape)
								{
									LightEmitterOwnedPtr emitter = dynamic_pointer_cast<LightEmitter>(shape);
									Vector3D ln;
									Spectrum ls;
									emitter->CalculateRadiance(lightIntersection.Position, ln, ls);
									lightPdf = emitter->CalculatePdf(lightIntersection.Position, rc);

									RayLight rayLight;
									rayLight.Radiance = ls;
									rayLight.Direction = -materialSampledVector;
									rayLight.Position = lightIntersection.Position;
									Spectrum lr = material->CalculateRadiance(rayLight, intersection);

									// convert material pdf to light area coordinates
									number mPdf = materialPdf * -lightIntersection.RayDirection.Dot(ln)
										/ (lightIntersection.Position-intersection.Position).LengthSquared();
									number wm = WeightByPowerHeuristic(mPdf, lightPdf);

									sum += lr * cos_in * wm / materialPdf;
								}
							}
						}
					}
					k++;
				}

				if (k > 0)
					r += throughput * (sum / (number)k);
			}

			// 3a. indirect lighting
			
			RayLight vr;
			vr.Direction = -materialSampledVector;
			vr.Position = intersection.Position;
			vr.Radiance = 1;

			// 3b. Russian roulette
			number q = depth < m_minDepth 
				? 0 
				: useAdaptiveRR ? 1-Math::Min(1., throughput.GetAverage()) : m_alpha;

			if ((samples[0]+samples[1])/2 < q)
				break;

			Spectrum f = material->CalculateRadiance(vr, intersection);
			throughput = throughput * f * (-vr.Direction.Dot(intersection.Normal) / (materialPdf * (1-q)));

			// 4. set new direction
			incoming.Direction = -vr.Direction;
			incoming.Position = intersection.Position + epsilon*incoming.Direction;

			m_calculationCount++;
			depth++;
		}

		m_pathCount++;
		result.Radiance = r;
	}
}

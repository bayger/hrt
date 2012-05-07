/*
* H-RT Core - the core of the H-RayTracer ray tracing renderer.
* Copyright (c) Patryk Bajer, H-RT.
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*/

#include "stdafx.h"
#include "DeterministicIntegrator.h"
#include "../Intersection.h"
#include "../Material.h"

namespace Hrt
{

  void DeterministicIntegrator::CalculateLight(const Ray& ray, Scene& scene,
    RayLight& result, unsigned level, RenderingContext& rc) const
  {
    // setup result
    result.Direction = -ray.Direction;
    result.Position.Set(0, 0, 0);
    result.Radiance = 0;

    // find ray intersection with the scene
    Intersection intersection;
    if (scene.GetGeometry()->Intersect(ray, &intersection))
    {
      MaterialPtr material = intersection.HitPrimitive->GetMaterial();
      number phi = intersection.Normal.Dot(-intersection.RayDirection);
      result.Position = intersection.Position;

      RayLight reflected;
      RayLight incident;

      Spectrum radiance;

      // receive rays from all lights in the scene
      for(uint k=0; k<scene.GetLightCount(); k++)
      {
        int i = 0;

        LightOwnedPtr light = rc.GetLights()[k];// scene.GetLight(k);
        light->Prepare(intersection.Position, intersection.Normal, rc);
        bool isDelta = light->IsDeltaLight();

        // this will be sum of reflected light from the current light source
        RayLight sum;

        // get all rays from the current light (MC-integration)
        number lightPdf;
        while(light->GenerateRayLight(&incident, lightPdf, rc))
        {
          // check if the ray is visible from the intersection-point
          if (scene.GetGeometry()->CheckVisibility(incident.Position,
            intersection.Position))
          {
            RayLight reflectedLight;
            material->CalculateReflectedRay(incident, intersection,
              reflectedLight, false);

            if (isDelta)
              reflectedLight.Radiance *= phi;
            else
              reflectedLight.Radiance *= phi
              * Math::Abs(incident.Direction.Dot(incident.LightNormal))
              / ((intersection.Position-incident.Position).LengthSquared() * lightPdf);

            sum = sum + reflectedLight;
          }
          i++;
        }

        // add integrated light from the current source to the final result
        if (i > 0) // skip if no ray was cast from the light source
        {
          sum.Radiance /= (number)i;
          result = result + sum;
        }
      }

      // reflected ray (as delta light)
      if (level < m_maxLevel)
      {
        // this will be ray light from reflection
        RayLight fromReflection;

        Vector3D reflected = ray.Direction.Reflect(intersection.Normal);
        Ray reflectedRay;
        reflectedRay.Direction = -reflected;
        reflectedRay.MediumRefractionIm = ray.MediumRefractionIm;
        reflectedRay.MediumRefractionRe = ray.MediumRefractionRe;
        reflectedRay.Position = intersection.Position +
          (intersection.Normal*epsilon);

        CalculateLight(reflectedRay, scene, fromReflection, level+1, rc);
        number distance2 = (fromReflection.Position - intersection.Position)
          .LengthSquared();

        // apply reflected ray of light to the result
        RayLight reflectedSpecular;
        material->CalculateReflectedRay(fromReflection, intersection,
          reflectedSpecular, true);
        reflectedSpecular.Radiance *= phi * phi / distance2 * (1/Consts::TwoPi);

        result = result + reflectedSpecular;
      }
    }
  }

}

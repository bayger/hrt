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

#ifndef _LIGHTINTEGRATOR_H
#define	_LIGHTINTEGRATOR_H

#include "Common.h"
#include "RayLight.h"
#include "Scene.h"
#include "RenderingContext.h"

namespace Hrt
{
    
    /// \brief Base class for light-integrators.
    /// Light integrator is an object that calculates incident ray of light based on
    /// position and direction of such ray and scene when the ray is cast off. It should
    /// be stateless object.
    class LightIntegrator
    {
    public:
        /// Calculates incident ray of light cast in the specified scene.
        virtual void CalculateLight(const Ray& ray, Scene& scene, RayLight& result,
                unsigned level, RenderingContext& rc) const =0;

				virtual int GetMaxLevels() const =0;
    };
    
		/// Reference to const shared-pointer of LightIntegrator (used as params and returns)
		typedef const shared_ptr<LightIntegrator>& LightIntegratorPtr;

		/// Shared-pointer of LightIntegrator (version for owners)
		typedef shared_ptr<LightIntegrator> LightIntegratorOwnedPtr;

}

#endif	/* _LIGHTINTEGRATOR_H */


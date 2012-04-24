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
#include "Common.h"
#include "Ray.h"
#include "Spectrum.h"
#include "PolarizationMatrix.h"

namespace Hrt
{
	/// Represents a ray of light
    struct RayLight : public Ray 
    {
    public:
        Spectrum Radiance;
        Vector3D LightNormal;
        
        // --- polarization ---
        Vector3D PolarizationVector;
        PolarizationMatrix Polarization[Spectrum::LambdaCount];
        
        // --- operators ---
        
        /// Just copies content of other ray to this one.
        RayLight& operator=(const RayLight& otherRay)
        {
            Radiance = otherRay.Radiance;
            LightNormal = otherRay.LightNormal;
            
            PolarizationVector = otherRay.PolarizationVector;
            for(unsigned i=0; i<Spectrum::LambdaCount; i++)
                Polarization[i] = otherRay.Polarization[i];
            
            return *this;
        }
        
        /// Adds one ray of light to the another.
        RayLight operator+(const RayLight& otherRay) 
        {
            RayLight result;
            // TODO: check polarization vector ?
            
            for(unsigned i = 0; i<Spectrum::LambdaCount; i++) 
            {
                result.Radiance[i] = Radiance[i] + otherRay.Radiance[i];
                PolarizationMatrix::WeightedAdd(Radiance[i], Polarization[i],
                        otherRay.Radiance[i], otherRay.Polarization[i],
                        result.Polarization[i]);
            }
            
            return result;
        }
    };
}

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
#pragma once
#include "../Common.h"
#include "../Material.h"
#include "PrecomputedImportanceSampler.h"

namespace Hrt
{
    
    class SimpleHe : public Material, public enable_shared_from_this<SimpleHe>
    {
    public:
        SimpleHe();
        SimpleHe(number gamma, number sigma, const Spectrum& a);
        
        virtual Spectrum CalculateBsdf(const RayLight& incomingRay,
                const Intersection& intersection,
                LightingType::Enum lightingType);

				virtual Vector3D SampleVector(number* sample, const Vector3D& outgoingDirection, 
					const Vector3D& tangentU, const Vector3D& tangentV, const Vector3D& n, number& pdf);

				virtual number CalculatePdf(const Vector3D& outgoingDirection, const Vector3D& tangentU, const Vector3D& tangentV, 
					const Vector3D& n, const Vector3D& incomingDirection);

        number Gamma() const
        { return gamma; }
        void Gamma(number gamma)
        {
            this->gamma = gamma;
            isPrecalcDirty = true;
        }
        
        number Sigma() const
        { return sigma; }
        void Sigma(number sigma)
        {
            this->sigma = sigma;
            isPrecalcDirty = true;
        }
        
        const Spectrum& A() const
        { return a; }
        void A(const Spectrum& a)
        { this->a = a; }

				virtual const std::string GetSignature();
        virtual void Initialize() { importanceSampler->Precompute(shared_from_this()); }
        
        // IYamlSerializable Implementation
        virtual bool ProcessYamlScalar(YamlParser& parser, SerializationContext& context);
        virtual const std::string& YamlType();
        
    private:
        static const unsigned int DistributionIterations = 350;
        static const unsigned int DPartResolution = 500;
        
        number gamma;
        number sigma;
        Spectrum a;
        boost::scoped_array<number> z0Precalc;
        boost::scoped_array<Spectrum> dPartPrecalc;
        bool isPrecalcDirty;
				shared_ptr<PrecomputedImportanceSampler> importanceSampler;
        
        number CalcZ0(number theta_i, number theta_r);
        number CalcShadowing(number theta_i, number theta_r);
        number CalcShadowingPart(number cot);
        number CalcDiffuseDistribution(number vxy, number g, number expMinusg, number lambda,
                number cos_i_r, unsigned int lambdaIndex);
        number GetPrecaledZ0(number theta_i, number theta_r);
        void PrecalculateZ0();
        number GetPrecalcedDPart(number cos_i_r, unsigned int lambdaIndex, unsigned int m);
        void PrecalculateDPart();
    };
    
}


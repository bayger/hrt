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
#include "SimpleHe.h"
#include "FresnelHelper.h"
#include "../Serialization/SerializationHelper.h"
#include "PrecomputedImportanceSampler.h"

namespace Hrt
{
    
    SimpleHe::SimpleHe(number gamma, number sigma, const Spectrum& a)
    : gamma(gamma), sigma(sigma), a(a), isPrecalcDirty(true), importanceSampler(new PrecomputedImportanceSampler)
    {
    }
    
    SimpleHe::SimpleHe()
    : gamma(0.38e-6), sigma(2e-6), a(0), isPrecalcDirty(true), importanceSampler(new PrecomputedImportanceSampler)
    {
    }

		/* Solves y=x*exp(x^2) for x given y */
		static inline number solve_xexpx2(number y)
		{
      const int iterations = 8; // more iterations == better quality of the result
      // NOTE: don't go below 8, because it will degrade performance in the next stages of calculations
      // due to inaccuracy of the result; use 16 for extremely accurate results (2-3% impact on performance)

			number x=(y>1)?sqrt(log(y)):y;
			int i;
			if (y > 3.0)
				for (i=0;i<iterations;i++)
					x=sqrt(log(y/x));
			else
				for (i=0;i<iterations;i++)
					x=0.5*(x+y*exp(-(x*x)));
			return x;
		}

    /* Solves y=x*exp(x) for x given y */
    static inline number solve_xexpx(number y)
    {
      const int max_iterations = 10000;
      
      // NOTE: seed is tweaked to avoid NaNs
      number x = y < 500 ? 1.0 : 100.0; 
      int i = 0;
      number err = 0.0;
      do
      {
        x = x - (x * Math::Exp(x) - y) / ((x + 1) * Math::Exp(x));
        err = (x*Math::Exp(x) - y)/y;
        i++;
      } while (err > 0.001 && i < max_iterations);

      return x;
    }

		static inline number CalculateSigma(number sigma0, number gamma, number theta_i, number theta_r)
		{
			number K_i = Math::Tan(theta_i)*Math::Erfc((gamma*Math::Ctg(theta_i)) / (2*sigma0));
			number K_r = Math::Tan(theta_r)*Math::Erfc((gamma*Math::Ctg(theta_r)) / (2*sigma0));
      number two_K2_over_PI = 2*Math::Square(K_i+K_r) / Consts::Pi;
      number squared_z0_over_sigma0 = solve_xexpx(two_K2_over_PI);
			return sigma0/Math::Sqrt(1 + (squared_z0_over_sigma0));
		}

    Spectrum SimpleHe::CalculateBsdf(const RayLight& incomingRay,
            const Intersection& intersection,
            LightingType::Enum lightingType)
    {
        Spectrum result;
        // convert input vectors to tangent space of the surface
        // tangent space: [tangentU, tangentV, Normal]
        Vector3D k_i = incomingRay.Direction.Transform(intersection.TangentU,
                intersection.TangentV, intersection.Normal);
        Vector3D k_r = (-intersection.RayDirection).Transform(intersection.TangentU,
                intersection.TangentV, intersection.Normal);
        
        number cos_theta_i = Vector3D::UnitZ*-k_i;
        number cos_theta_r = Vector3D::UnitZ*k_r;
        
				if (cos_theta_i <= 0 || cos_theta_r <= 0 || cos_theta_r > 1 || cos_theta_i > 1)
        {
            return result;
        }
        
        Vector3D s_i = k_i.Cross(Vector3D::UnitZ).Normalize();
        Vector3D p_i = s_i.Cross(k_i);
        
        Vector3D s_r = k_r.Cross(Vector3D::UnitZ).Normalize();
        Vector3D p_r = s_r.Cross(k_r);
        
        // calc angles
        number theta_i = Math::Arcos(cos_theta_i);
        number theta_r = Math::Arcos(cos_theta_r);
        //number z_0 = CalcZ0(theta_i, theta_r);

				number sigma2 = CalculateSigma(sigma, gamma, theta_i, theta_r);
        
        number vh = (-intersection.RayDirection-incomingRay.Direction).Normalize()
                .Dot(-intersection.RayDirection);
        
        // check if in specular cone
        bool isInSpecularCone = (lightingType & LightingType::IdealSpecular) != 0;
        
        // make calculation for every lambda in the spectrum
        for(int lambdaIndex = 0; lambdaIndex < Spectrum::LambdaCount; lambdaIndex++)
        {
            number lambda = Spectrum::IndexToLambda(lambdaIndex);
            
            // refractive indices and angles
            complexNumber n1(incomingRay.MediumRefractionRe[lambdaIndex],
                    incomingRay.MediumRefractionIm[lambdaIndex]);
            complexNumber n2(m_refractionRe[lambdaIndex], m_refractionIm[lambdaIndex]);
            
            complexNumber complex_cos_theta_t = Math::Sqrt( num(1) - Math::Square(n1/n2)
                    * (1 - vh*vh) );
            number cos_theta_t = complex_cos_theta_t.real();
            
            if (gsl_isnan(cos_theta_t))
            { // total internal reflection
                result[lambdaIndex] = isInSpecularCone
                        ? incomingRay.Radiance[lambdaIndex]
                        : 0;
                continue;
            }
            
            // Fresnel coefficients for polarized light
            number F_s = 0;
            number F_p = 0;
            FresnelHelper::CalcFresnel3(m_refractionRe[lambdaIndex],
                    m_refractionIm[lambdaIndex], Math::Arcos(vh), F_s, F_p);
            
            // Calculate geometrical attenuation factor and v
            // (note the differences from the paper: v and v2 are different)
            Vector3D v = k_r - k_i;
            number v_xy = Math::Sqrt(v.X*v.X + v.Y*v.Y);
            Vector3D k_p = k_r.Cross(k_i);
            
            number G = (Math::Square(v.Dot(v)/v.Z) * (1/Math::Square(k_p.LengthSquared()))
                    * (Math::Square(s_r*k_i) + Math::Square(p_r*k_i))
                    * (Math::Square(s_i*k_r) + Math::Square(p_i*k_r)));
            // NOTE: G may be #INF for v.Z == 0 or |k_p| == 0
            
            // Fresnel for unpolarized light
            number F2 = gsl_isnan(cos_theta_t) ? 0 : (F_s+F_p) / 2;
            
            // Shadowing function calculation
            number S = CalcShadowing(theta_i, theta_r);
            
            // Distribution function            
            number g = Math::Square( (Consts::TwoPi*sigma2 / lambda)
                    * (cos_theta_i + cos_theta_r) );
            number exp_minus_g = Math::Exp(-g);
            number D = CalcDiffuseDistribution(v_xy, g, exp_minus_g, lambda,
                    cos_theta_r+cos_theta_i, lambdaIndex);
            
            // Final components
            number delta_func = isInSpecularCone ? 1 : 0;
            number rho_s = F2 * exp_minus_g * S;
            number rho_sp = rho_s * delta_func;
            number rho_dd = (F2 / Consts::Pi) * ((G*S*D)/(cos_theta_r*cos_theta_i));
            number rho_ud = a[lambdaIndex] * cos_theta_i;
            
            result.Values[lambdaIndex] = (rho_sp + rho_dd + rho_ud)
                    * incomingRay.Radiance.Values[lambdaIndex];
        }
        
        return result;
    }
    
    Hrt::number SimpleHe::CalcShadowing( number theta_i, number theta_r )
    {
        number cot_theta_i = Math::Ctg(theta_i);
        number cot_theta_r = Math::Ctg(theta_r);
        
        return CalcShadowingPart(cot_theta_i)*CalcShadowingPart(cot_theta_r);
    }
    
    Hrt::number SimpleHe::CalcShadowingPart( number cot )
    {
        // Formula (24) from the paper was corrected by He at
        // http://groups.google.pl/group/comp.graphics/browse_thread/thread/568bb1272c5a4694/bc3174f3df05d9fe?hide_quotes=no#msg_bc3174f3df05d9fe
        number gamma_cot_by_2sigma = (gamma*cot) / (2*sigma);
        number erfc = Math::Erfc(gamma_cot_by_2sigma);
        number lambda = ((1/gamma_cot_by_2sigma/Consts::SqrtPi)
                * Math::Exp(-Math::Square(gamma_cot_by_2sigma)) // << missing in the paper [He]
                - erfc)/2;
        
        return (1 - erfc/2 ) / (lambda + 1);
    }


		static inline number Htsg_sum(number g, number T)
		{
			// T = -v_xy^2*(PI*tau/lamda)^2
			if (g < 15) {
				number sum=0;
				int m=1;
				number term1=Math::Exp(-g);
				for (;m<40;m++) {
					register number recm=(1.0/(number)m);
					term1*=g*recm;
					sum += term1*recm*Math::Exp(T*recm);
				}
				return sum;
			}
			number mx=g;
			int i;
			for (i=0;i<4;i++)
				mx=g*Math::Exp(-1.5/mx-T/Math::Square(mx));
			return Math::Sqrt(g)*Math::Exp(mx*log(g)-g-(mx+1.5)*log(mx)+mx+T/mx);
		}

    
    Hrt::number SimpleHe::CalcDiffuseDistribution(number vxy, number g,
            number expMinusg, number lambda, number cos_i_r, unsigned int lambdaIndex)
    {
			number pi_gamma_by_lambda = Consts::Pi*gamma/lambda;
			number T = -(vxy*vxy)*(pi_gamma_by_lambda*pi_gamma_by_lambda);

			number x = Consts::Pi*gamma/lambda/2;
			return x*x*Htsg_sum(g, T);
    }
    
    
    
    
    bool SimpleHe::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
    {
        std::string scalarValue = parser.CurrentValue();
        if (scalarValue == "sigma")
            parser.ReadScalar(sigma);
        else if (scalarValue == "tau")
            parser.ReadScalar(gamma);
        else if (scalarValue == "refractive-real")
            m_refractionRe = SerializationHelper::ReadSpectrum(parser);
        else if (scalarValue == "refractive-imaginary")
            m_refractionIm = SerializationHelper::ReadSpectrum(parser);
        else
            return NamedObject::ProcessYamlScalar(parser, context);
        
        return true;
    }
    
    static std::string yamlType("htsg");
    const std::string& SimpleHe::YamlType()
    {
        return yamlType;
    }

		Hrt::Vector3D SimpleHe::SampleVector(number* sample, const Vector3D& outgoingDirection, const Vector3D& tangentU, const Vector3D& tangentV, const Vector3D& n, number& pdf)
		{
			//return Material::SampleVector(sample, outgoingDirection, tangentU, tangentV, n, pdf);
			return importanceSampler->SampleVector(sample, outgoingDirection, tangentU, tangentV, n, pdf);
		}

		void SimpleHe::Precalculate()
		{
			importanceSampler->Precompute(shared_from_this());
		}


		const std::string SimpleHe::GetSignature()
		{
			return str(format("%1%:s=%2%,t=%3%,rr=%4%,ri=%5%") % yamlType % sigma % gamma % m_refractionRe.ToString() % m_refractionIm.ToString());
		}

		Hrt::number SimpleHe::CalculatePdf(const Vector3D& outgoingDirection, const Vector3D& tangentU, const Vector3D& tangentV, const Vector3D& n, const Vector3D& incomingDirection)
		{
			//return Material::CalculatePdf(incomingDirection, outgoingDirection, tangentU, tangentV, n);
			return importanceSampler->GetPdf(incomingDirection, outgoingDirection, tangentU, tangentV, n);
		}

}

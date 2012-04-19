#pragma once
#include <complex>
#include "../PolarizationMatrix.h"

namespace Hrt
{

	class FresnelHelper
	{
	public:
		/// \brief Computes the Fresnel term of reflectance equations
		/// This is a version that uses only real numbers. Seems to work correctly.
		static void CalculateFresnel(const Spectrum& n1Re, const Spectrum& n1Im,
			const Spectrum& n2Re, const Spectrum& n2Im, number cosThetaI,
			number cosThetaT, int lambdaIndex, number& Fs, number& Fr)
		{
			number n1_cos_theta_i = n1Re[lambdaIndex] * cosThetaI;
			number n1_cos_theta_t = n1Re[lambdaIndex] * cosThetaT;
			number n2_cos_theta_i = n2Re[lambdaIndex] * cosThetaI;
			number n2_cos_theta_t = n2Re[lambdaIndex] * cosThetaT;

			number f_s = (n1_cos_theta_i - n2_cos_theta_t)
				/ (n1_cos_theta_i + n2_cos_theta_t);
			Fs = f_s * f_s;

			number f_r = (n1_cos_theta_t - n2_cos_theta_i)
				/ (n1_cos_theta_t + n2_cos_theta_i);
			Fr = f_r * f_r;
			
		}

		/// \brief Another method that computes Fresnel term.
		/// This one is using full complex number calculation, but unfortunately
		/// returns wrong results. Colors are incorrect. DO NOT USE!
		static void CalculateFresnelComplex(const Spectrum& n1Re, const Spectrum& n1Im,
			const Spectrum& n2Re, const Spectrum& n2Im, number cosThetaI,
			number cosThetaT, int lambdaIndex, number& Fs, number& Fr)
		{
			complexNumber n1(n1Re[lambdaIndex], n1Im[lambdaIndex]);
			complexNumber n2(n2Re[lambdaIndex], n2Im[lambdaIndex]);

			complexNumber n1_cos_theta_i = n1 * cosThetaI;
			complexNumber n1_cos_theta_t = n1 * cosThetaT;
			complexNumber n2_cos_theta_i = n2 * cosThetaI;
			complexNumber n2_cos_theta_t = n2 * cosThetaT;

			complexNumber f_s = (n1_cos_theta_i - n2_cos_theta_t)
			/ (n1_cos_theta_i + n2_cos_theta_t);
			Fs = (f_s*f_s).real();

			complexNumber f_r = (n1_cos_theta_t - n2_cos_theta_i)
			/ (n1_cos_theta_t + n2_cos_theta_i);
			Fr = (f_r*f_r).real();
		}

		static void CalcFresnel3(number n, number k, number theta_i, 
			number& F_s, number& F_r)
		{
			number nn = n*n;
			number kk = k*k;
			number cos_i = Math::Cos(theta_i);
			number sin_i = Math::Sin(theta_i);
			number cos2_i = cos_i * cos_i;
			number sin2_i = sin_i * sin_i;
			number tan_i = sin_i / cos_i;
			number tan2_i = tan_i * tan_i;

			number sr = Math::Sqrt(Math::Square(nn - kk - sin2_i) + 4*nn*kk);
			number aa2 = sr	+ nn - kk - sin2_i;
			number bb2 = sr - nn + kk + sin2_i;
			number aa = aa2 / 2;
			number bb = bb2 / 2;
			number a2 = 2*Math::Sqrt(aa);

			F_s = (aa + bb - a2*cos_i + cos2_i)
				/ (aa + bb + a2*cos_i + cos2_i);
			F_r = (aa + bb - a2*sin_i*tan_i + sin2_i*tan2_i)
				/ (aa + bb + a2*sin_i*tan_i + sin2_i*tan2_i) * F_s;
		}

	private:
		FresnelHelper(void);
	};


	/// Creates a new polarization matrix for Fresnel light reflection.
	//static PolarizationMatrix Reflect()
	//{
	//	complexNumber retardance;
	//	retardance.imag(1); retardance.real(0);

	//	number coeff = 1 / (F_s*Jxx + F_p*Jyy);
	//	complexNumber root = Math::Sqrt((complexNumber)(F_s*F_p));

	//	PolarizationMatrix result;
	//	result.Jxx = coeff * (F_s*Jxx);
	//	result.Jxy = coeff * root * Jxy * Math::Exp(retardance)
	//}
}

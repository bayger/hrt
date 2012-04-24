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
#include "Spectrum.h"
#include "CieXyz.h"
#include "Math.h"

namespace Hrt
{

#ifdef HRT_USE_RGB

	/// RGB to CIE XYZ color matching (sRGB D65)
	const number Spectrum::XyzMatching[LambdaCount][3] = {
		{(number)0.180464,   (number)0.0721856,  (number)0.950444}, // BLUE
		{(number)0.357579,   (number)0.715158,   (number)0.119193 }, // GREEN
		{(number)0.412424,   (number)0.212656,   (number)0.0193324}  // RED
	};

	number Spectrum::GetValueFor(number lambda)
	{
		throw NotImplementedException("GetValueFor is not implemented for RGB Spectrum");
	}

#else

	/// CIE XYZ color matching function (sampled every 5 nm) 380 - 780 nm
	/// Taken from http://www.fourmilab.ch/documents/specrend/specrend.c by John Walker
	const number Spectrum::XyzMatching[LambdaCount][3] = {
		{(number)0.0014,(number)0.0000,(number)0.0065}, 
		{(number)0.0022,(number)0.0001,(number)0.0105}, 
		{(number)0.0042,(number)0.0001,(number)0.0201},
		{(number)0.0076,(number)0.0002,(number)0.0362}, 
		{(number)0.0143,(number)0.0004,(number)0.0679}, 
		{(number)0.0232,(number)0.0006,(number)0.1102},
		{(number)0.0435,(number)0.0012,(number)0.2074}, 
		{(number)0.0776,(number)0.0022,(number)0.3713}, 
		{(number)0.1344,(number)0.0040,(number)0.6456},
		{(number)0.2148,(number)0.0073,(number)1.0391}, 
		{(number)0.2839,(number)0.0116,(number)1.3856}, 
		{(number)0.3285,(number)0.0168,(number)1.6230},
		{(number)0.3483,(number)0.0230,(number)1.7471}, 
		{(number)0.3481,(number)0.0298,(number)1.7826}, 
		{(number)0.3362,(number)0.0380,(number)1.7721},
		{(number)0.3187,(number)0.0480,(number)1.7441}, 
		{(number)0.2908,(number)0.0600,(number)1.6692}, 
		{(number)0.2511,(number)0.0739,(number)1.5281},
		{(number)0.1954,(number)0.0910,(number)1.2876}, 
		{(number)0.1421,(number)0.1126,(number)1.0419}, 
		{(number)0.0956,(number)0.1390,(number)0.8130},
		{(number)0.0580,(number)0.1693,(number)0.6162}, 
		{(number)0.0320,(number)0.2080,(number)0.4652}, 
		{(number)0.0147,(number)0.2586,(number)0.3533},
		{(number)0.0049,(number)0.3230,(number)0.2720}, 
		{(number)0.0024,(number)0.4073,(number)0.2123}, 
		{(number)0.0093,(number)0.5030,(number)0.1582},
		{(number)0.0291,(number)0.6082,(number)0.1117}, 
		{(number)0.0633,(number)0.7100,(number)0.0782}, 
		{(number)0.1096,(number)0.7932,(number)0.0573},
		{(number)0.1655,(number)0.8620,(number)0.0422}, 
		{(number)0.2257,(number)0.9149,(number)0.0298}, 
		{(number)0.2904,(number)0.9540,(number)0.0203},
		{(number)0.3597,(number)0.9803,(number)0.0134}, 
		{(number)0.4334,(number)0.9950,(number)0.0087}, 
		{(number)0.5121,(number)1.0000,(number)0.0057},
		{(number)0.5945,(number)0.9950,(number)0.0039}, 
		{(number)0.6784,(number)0.9786,(number)0.0027}, 
		{(number)0.7621,(number)0.9520,(number)0.0021},
		{(number)0.8425,(number)0.9154,(number)0.0018}, 
		{(number)0.9163,(number)0.8700,(number)0.0017}, 
		{(number)0.9786,(number)0.8163,(number)0.0014},
		{(number)1.0263,(number)0.7570,(number)0.0011}, 
		{(number)1.0567,(number)0.6949,(number)0.0010}, 
		{(number)1.0622,(number)0.6310,(number)0.0008},
		{(number)1.0456,(number)0.5668,(number)0.0006}, 
		{(number)1.0026,(number)0.5030,(number)0.0003}, 
		{(number)0.9384,(number)0.4412,(number)0.0002},
		{(number)0.8544,(number)0.3810,(number)0.0002}, 
		{(number)0.7514,(number)0.3210,(number)0.0001}, 
		{(number)0.6424,(number)0.2650,(number)0.0000},
		{(number)0.5419,(number)0.2170,(number)0.0000}, 
		{(number)0.4479,(number)0.1750,(number)0.0000}, 
		{(number)0.3608,(number)0.1382,(number)0.0000},
		{(number)0.2835,(number)0.1070,(number)0.0000}, 
		{(number)0.2187,(number)0.0816,(number)0.0000}, 
		{(number)0.1649,(number)0.0610,(number)0.0000},
		{(number)0.1212,(number)0.0446,(number)0.0000}, 
		{(number)0.0874,(number)0.0320,(number)0.0000}, 
		{(number)0.0636,(number)0.0232,(number)0.0000},
		{(number)0.0468,(number)0.0170,(number)0.0000}, 
		{(number)0.0329,(number)0.0119,(number)0.0000}, 
		{(number)0.0227,(number)0.0082,(number)0.0000},
		{(number)0.0158,(number)0.0057,(number)0.0000}, 
		{(number)0.0114,(number)0.0041,(number)0.0000}, 
		{(number)0.0081,(number)0.0029,(number)0.0000},
		{(number)0.0058,(number)0.0021,(number)0.0000}, 
		{(number)0.0041,(number)0.0015,(number)0.0000}, 
		{(number)0.0029,(number)0.0010,(number)0.0000},
		{(number)0.0020,(number)0.0007,(number)0.0000}, 
		{(number)0.0014,(number)0.0005,(number)0.0000}, 
		{(number)0.0010,(number)0.0004,(number)0.0000},
		{(number)0.0007,(number)0.0002,(number)0.0000}, 
		{(number)0.0005,(number)0.0002,(number)0.0000}, 
		{(number)0.0003,(number)0.0001,(number)0.0000},
		{(number)0.0002,(number)0.0001,(number)0.0000}, 
		{(number)0.0002,(number)0.0001,(number)0.0000}, 
		{(number)0.0001,(number)0.0000,(number)0.0000},
		{(number)0.0001,(number)0.0000,(number)0.0000}, 
		{(number)0.0001,(number)0.0000,(number)0.0000}, 
		{(number)0.0000,(number)0.0000,(number)0.0000}
	};


	number Spectrum::GetValueFor(number lambda)
	{
		if (lambda < MinLambda || lambda > MaxLambda)
			return 0;

		// exact value?
		if (lambda == (int)lambda && (((int)lambda % LambdaStep) == 0))
		{
			int i = (int)((lambda - MinLambda) / LambdaStep);
			return Values[i];
		}

		// linear interpolation
		number k = ((number)(lambda-MinLambda) / LambdaStep);
		int i = (int)Math::Floor(k);
		number t = k-i;

		return Values[i]*t + Values[i+1]*(1-t);
	}

#endif

	Spectrum::Spectrum(void)
	{
		for(int i=0; i<LambdaCount; i++)
			Values[i] = 0;
	}

	Spectrum::Spectrum(number c)
	{
		for(int i=0; i<LambdaCount; i++)
			Values[i] = c;
	}


	CieXyz Spectrum::ToCieXyz() const
	{
		CieXyz xyz;
		xyz.X = xyz.Y = xyz.Z = 0;
		for(int i=0; i<LambdaCount; i++)
		{
			xyz.X += XyzMatching[i][0]*Values[i];
			xyz.Y += XyzMatching[i][1]*Values[i];
			xyz.Z += XyzMatching[i][2]*Values[i];
		}

		return xyz;
	}

	void Spectrum::Normalize(number maximum)
	{
		number recip = 1/maximum;
		for(int i=0; i<LambdaCount; i++)
			Values[i] = Values[i] < maximum ? Values[i]*recip : 1;
	}

	void Spectrum::Invert()
	{
		for(int i=0; i<LambdaCount; i++)
			Values[i] = 1-Values[i];
	}

	std::string Spectrum::ToString() const
	{
#ifdef HRT_USE_RGB
		return str(format("(%1%,%2%,%3%)") % Values[0] % Values[1] % Values[2]);
#else
		return "Spectrum";
#endif
	}

	Spectrum operator*(const Spectrum& color, number mul)
	{
		Spectrum result;
		for(int i=0; i<Spectrum::LambdaCount; i++)
			result.Values[i] = mul*color.Values[i];

		return result;
	}

	Spectrum operator*(number mul, const Spectrum& color)
	{
		Spectrum result;
		for(int i=0; i<Spectrum::LambdaCount; i++)
			result.Values[i] = mul*color.Values[i];

		return result;
	}

	const Spectrum Spectrum::Uniform(1);
	const Spectrum Spectrum::Zero(0);


}

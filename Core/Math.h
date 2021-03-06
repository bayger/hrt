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
#define DONT_USE_MATH_DEFINES
#include "Common.h"
#include <math.h>
#include "External/MersenneTwister.h"
#include "Exceptions.h"

namespace Hrt
{
	namespace Consts
	{
		const number Pi = (number)3.1415926535897932384626433832795;
		const number HalfPi = (number)3.1415926535897932384626433832795/2;
		const number TwoPi = (number)Pi*2;
		const number FourPi = (number)Pi*4;
		const number SqrtPi = (number)1.7724538509055160272981674833411;
		const number SqrtHalfPi = (number)1.2533141373155002512078826424055;
		const number SquaredPi = (number)9.8696044010893586188344909998762;
	}

	/// Provides math methods used in HRT.
	class Math
	{
	public:
		/// Returns square root of a value
		static inline number Sqrt(number value)
		{
			return sqrt(value);
		}

		static inline complexNumber Sqrt(complexNumber value)
		{
			return sqrt(value);
		}

		static inline number Square(number value)
		{
			return value*value;
		}

		static inline complexNumber Square(complexNumber value)
		{
			return value*value;
		}

		/// Returns cotangent for given value.
		static inline number Ctg(number value)
		{
			return (number)(1.0 / tan(value));
		}

		static inline complexNumber Ctg(complexNumber value)
		{
			return ((number)1)/tan(value);
		}

		static inline number Atan(number x, number y)
		{
			return num(::atan2(y, x));
		}

		/// Returns the nearest integral value
		static inline number Round(number value)
		{
			return (number)(value - floor(value) >= 0.5 ? ceil(value) : floor(value));
		}

		/// Returns the "floor" value of a number.
		static inline number Floor(number value)
		{
			return (number)floor(value);
		}

		/// Returns the "ceiling" value of a number.
		static inline number Ceiling(number value)
		{
			return (number)ceil(value);
		}

		/// Returns the absolute value.
		static inline number Abs(number val)
		{
			return fabs(val);
		}

		/// Returns the absolute value (integer version).
		static inline int Abs(int val)
		{
			return val >= 0 ? val : -val;
		}

		/// Returns maximum value of v1, v2.
		static inline number Max(number v1, number v2)
		{
			return v1 > v2 ? v1 : v2;
		}

		/// Returns maximum value of v1, v2.
		static inline int Max(int v1, int v2)
		{
			return v1 > v2 ? v1 : v2;
		}

		/// Returns maximum value of v1, v2, v3.
		static inline int Max(int v1, int v2, int v3)
		{
			return Max(v1, Max(v2, v3));
		}

		/// Returns maximum value of v1, v2, v3.
		static inline number Max(number v1, number v2, number v3)
		{
			return Max(v1, Max(v2, v3));
		}

		/// Returns minimum value of v1, v2.
		static inline number Min(number v1, number v2)
		{
			return v1 < v2 ? v1 : v2;
		}

		/// Returns minimum value of v1, v2.
		static inline int Min(int v1, int v2)
		{
			return v1 < v2 ? v1 : v2;
		}

		/// Returns minimum value of v1, v2, v3.
		static inline int Min(int v1, int v2, int v3)
		{
			return Min(v1, Min(v2, v3));
		}

		/// Returns minimum value of v1, v2, v3.
		static inline number Min(number v1, number v2, number v3)
		{
			return Min(v1, Min(v2, v3));
		}

		/// Calculates sin(val).
		static inline number Sin(number val)
		{
			return (number)sin(val);
		}

		static inline complexNumber Sin(complexNumber val)
		{
			return sin(val);
		}

		/// Calculates cos(val).
		static inline number Cos(number val)
		{
			return (number)cos(val);
		}

		static inline complexNumber Cos(complexNumber val)
		{
			return cos(val);
		}

		/// Computes n^k.
		static inline number Pow(number n, number k)
		{
			if (n < 0 && k != (int)k)
				throw InvalidArgumentException("Negative n and non-integer k are not supported");

			return (number)pow(n, k);
		}

		/// Computes tan(val)
		static inline number Tan(number val)
		{
			return (number)tan(val);
		}

		static inline complexNumber Tan(complexNumber val)
		{
			return tan(val);
		}

		/// Computes arcus cosinus of val.
		static inline number Arcos(number val)
		{
			return (number)acos(val);
		};

		/// Computes e^x.
		static inline number Exp(number x)
		{
			return (number)exp(x);
		}

		/// Computes e^x in the complex numbers domain.
		static inline complexNumber Exp(complexNumber x)
		{
			return exp(x);
		}

		/// Calculates the sinc function = sin(x)/x
		static inline number Sinc(number x)
		{
			return x != 0 ? Sin(x) / x : 1;
		}

		/// Calculates the erfc function (complementary error function).
		static number Erfc(number x);

		/// Calculates i!
		static number Factorial(unsigned int i);

		/// Calculates Taylor coefficient (x^n/n!)
		static number Taylor(number x, int n);

		/// Returns true is integer is power of two.
		static inline bool IsPow2(uint v)
		{
			return (v & (v - 1)) == 0;
		}

		static inline int GetPow2(uint v)
		{
			uint pow = 0x80000000;
			for(uint p=31; p>0; p--)
			{
				if ((v & pow) == v) return p;
				pow = pow >> 1;
			}

			return -1;
		}

    static bool Math::IsNan(number val)
    {
      return gsl_isnan(val) == 1;
    }

	private:
		Math(void) {}
    
  };

}

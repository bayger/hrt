/*
 * H-RT Core - the core of the H-RayTracer ray tracing renderer.
 * Copyright (c) 2006-2010 H-RT Team.
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
#include "Common.h"
#include "Exceptions.h"
#include "Math.h"

namespace Hrt
{
    struct CieXyz;
    
    
    /// Spectrum of light used in H-RT. This describes "a color" and
    /// is simply discretized visible light spectrum. It is easy to convert to
    /// the CIE XYZ, because it is internally based on the CIE XYZ color matching
    /// function table.
    /// It is also used as an absoption spectrum which describes how much of
    /// incident light is absopted by particular material or medium. Absoption
    /// spectrum must be normalized, so all values are in range [0,1].
    class Spectrum
    {
    public:
        
#ifdef HRT_USE_RGB
        
        // Values that defines range and resolution of a spectrum:
        static const int LambdaCount = 3;
        
        static const Spectrum Uniform;
        static const Spectrum Zero;
        
        /// Values of XYZ matching functions. Used in spectrum->XYZ convertion.
        static const number XyzMatching[LambdaCount][3];
        
        /// Gets the index in Values array for given wavelength lambda.
        static int inline LambdaToIndex(number lambda)
        {
            if (lambda == 0.0000007000)
                return 2;
            else if (lambda == 0.0000005461)
                return 1;
            else if (lambda == 0.0000004358)
                return 0;
            else
                throw new InvalidOperationException("Wavelength out of range!");
        }
        
        static number inline IndexToLambda(int index)
        {
            if (index == 0)
                return num(0.0000004358);
            else if (index == 1)
                return num(0.0000005461);
            else if (index == 2)
                return num(0.0000007000);
            else
                throw new InvalidOperationException("Index out of range!");
        }
        
#else
        
        // Values that defines range and resolution of a spectrum:
        static const int MinLambda = 380;
        static const int MaxLambda = 780;
        static const int LambdaStep = 5;
        static const int LambdaCount = (MaxLambda-MinLambda)/LambdaStep + 1;
        
        // Wavelengths of spectral colors (from http://en.wikipedia.org/wiki/Color#Spectral_colors):
        static const int Red = 700;
        static const int Orange = 620;
        static const int Yellow = 580;
        static const int Green = 530;
        static const int Blue = 470;
        static const int Violet = 420;
        
        static const Spectrum Uniform;
        static const Spectrum Zero;
        
        /// Values of XYZ matching functions. Used in spectrum->XYZ convertion.
        static const number XyzMatching[LambdaCount][3];
        
        /// Gets the index in Values array for given wavelength lambda.
        static int inline LambdaToIndex(number lambda)
        {
            if (lambda < MinLambda || lambda > MaxLambda)
                throw new InvalidOperationException("Wavelength out of range!");
            
            return (int)((lambda - MinLambda) / LambdaStep);
        }
        
        static number inline IndexToLambda(int index)
        {
            if (index >= LambdaCount || index < 0)
                throw new InvalidOperationException("Index out of range!");
            
            return (MinLambda + index*LambdaStep) * 0.000000001;
        }
        
#endif
        
    public:
        Spectrum();
        Spectrum(number c);

				bool operator<(const Spectrum& s)
				{
					return Values[0]+Values[1]+Values[2] < s.Values[0]+s.Values[1]+s.Values[2];
				}
        
				bool operator<(const Spectrum& s) const
				{
					return Values[0]+Values[1]+Values[2] < s.Values[0]+s.Values[1]+s.Values[2];
				}

        inline number& operator[](int index)
        {
            return Values[index];
        }
        
        inline number operator[](int index) const
        {
            return Values[index];
        }
        
        void SetValues(number* values)
        {
            for(int i=0; i<LambdaCount; i++)
                Values[i] = values[i];
        }
        
        /// Returns the value of spectrum for given lambda.
        number GetValueFor(number lambda);
        
        /// Converts spectrum to color in XYZ color-space.
        CieXyz ToCieXyz() const;
        
        /// Clear the spectrum to black (all Values are zeros).
        void SetBlack()
        {
            for(int i=0; i<LambdaCount; i++)
                Values[i] = 0;
        }

				void SetOne()
				{
					for(int i=0; i<LambdaCount; i++)
						Values[i] = 1;
				}

        bool IsZero() const
        {
            for(int i=0; i<LambdaCount; i++)
                if (Values[i] != 0)
                    return false;
            
            return true;
        }

        bool IsNan() const
        {
          for(int i=0; i<LambdaCount; i++)
            if (Math::IsNan(Values[i]))
              return true;

          return false;
        }

        /// Normalizes spectrum to given value. Useful for creating absorption spectrums.
        /// \param maximum Normalization value (maximum becomes 1.0 after normalization)
        /// \remarks All values above maximum value are clamped to 1.0
        void Normalize(number maximum);
        
        /// Inverts normalized spectrum.
        /// \remarks Valid only for normalized (absorption) spectrums.
        void Invert();
        
        Spectrum& operator=(number val)
        {
            for(int i=0; i<LambdaCount; i++)
                Values[i] = val;
            
            return *this;
        }
        
        Spectrum& operator*=(number mul)
        {
            for(int i=0; i<LambdaCount; i++)
                Values[i] *= mul;
            
            return *this;
        }
        
        Spectrum& operator/=(number val)
        {
            number recip = 1/val;
            for(int i=0; i<LambdaCount; i++)
                Values[i] *= recip;
            
            return *this;
        }
        
				Spectrum& operator/=(const Spectrum& val)
				{
					for(int i=0; i<LambdaCount; i++)
						Values[i] /= val.Values[i];

					return *this;
				}

        Spectrum& operator+=(const Spectrum& color)
        {
            for(int i=0; i<LambdaCount; i++)
                Values[i] += color.Values[i];
            
            return *this;
        }
        
        Spectrum& operator+=(number value)
        {
            for(int i=0; i<LambdaCount; i++)
                Values[i] += value;
            
            return *this;
        }
        
        Spectrum& operator-=(number value)
        {
            for(int i=0; i<LambdaCount; i++)
                Values[i] -= value;
            
            return *this;
        }
        
        Spectrum& operator-=(const Spectrum& color)
        {
            for(int i=0; i<LambdaCount; i++)
                Values[i] -= color.Values[i];
            
            return *this;
        }
        
        Spectrum operator+(const Spectrum& color) const
        {
            Spectrum result;
            for(int i=0; i<Spectrum::LambdaCount; i++)
                result.Values[i] = Values[i]+color.Values[i];
            
            return result;
        }

				Spectrum operator/(const Spectrum& color) const
				{
					Spectrum result;
					for(int i=0; i<Spectrum::LambdaCount; i++)
						result.Values[i] = Values[i] / color.Values[i];

					return result;
				}
        
        Spectrum operator-(const Spectrum& color) const
        {
            Spectrum result;
            for(int i=0; i<Spectrum::LambdaCount; i++)
                result.Values[i] = Values[i]-color.Values[i];
            
            return result;
        }
        
        Spectrum operator*(const Spectrum& absorption) const
        {
            Spectrum result;
            for(int i=0; i<Spectrum::LambdaCount; i++)
                result.Values[i] = Values[i]*absorption.Values[i];
            
            return result;
        }
        
        Spectrum operator/(number val) const
        {
            Spectrum result;
            number recip = 1/val;
            for(int i=0; i<Spectrum::LambdaCount; i++)
                result.Values[i] = Values[i]*recip;
            
            return result;
        }

				number GetAverage() const
				{
					number v = 0;
					for(int i=0; i<Spectrum::LambdaCount; i++)
						v += Values[i];

					return v/Spectrum::LambdaCount;
				}

				std::string ToString() const;
        
        number Values[LambdaCount];
    };
    
    Spectrum operator*(const Spectrum& color, number mul);
    Spectrum operator*(number mul, const Spectrum& color);
}

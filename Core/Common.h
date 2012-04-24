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
#define HRT_DONT_USE_FLOATS
#define HRT_USE_RGB
#include <complex>

#define AUTO_PROPERTY(var_type, var_name, prop_name) \
	const var_type Get##prop_name() const { return var_name; } \
	void Set##prop_name(const var_type val) { var_name = val; }

#define AUTO_GETTER(var_type, var_name, prop_name) \
	const var_type Get##prop_name() const { return var_name; }

#define AUTO_SETTER(var_type, var_name, prop_name) \
	void Set##prop_name(const var_type val) { var_name = val; }

namespace Hrt
{
#ifdef HRT_USE_FLOATS
	// NOTE: floats are almost 2 times slower on Core2Duo E6600
	// when compiled with VC++ 2005
	typedef float number;
	typedef std::complex<float> complexNumber;
	const number epsilon = (number)1.0e-6;
	const number zero = 0;
#else
	typedef double number;
	typedef std::complex<double> complexNumber;
	const number epsilon = (number)1.0e-12;
	const number zero = 0;
#endif

#define num(x) ((number)x)
	
	typedef unsigned int uint;
	typedef __int64 int64;

	class LibraryInfo
	{
	public:
		static uint GetVersion();
		static std::string GetFullName();
		static bool IsUsingFloats();
		static bool IsUsingRGBColor();

	private:
		LibraryInfo();
	};

	template<class T>
	class Singleton
	{
	public:
		static T& Instance();
	private:
		T t;

		Singleton();
		~Singleton();
	};

	template<class T>
	inline Singleton<T>::Singleton() { }

	template<class T>
	inline Singleton<T>::~Singleton() { }

	template<class T>
	T& Singleton<T>::Instance()
	{
		static Singleton<T> instance;
		return instance.t;
	}

}

#include <boost/enable_shared_from_this.hpp>
using namespace boost;

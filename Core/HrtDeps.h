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

#include <memory>	// for auto_ptr
#include <cassert>  // for assert
#include <algorithm>
#include <vector>
#include <complex>
#include <iostream>
#include <iomanip>

#ifdef __GNUG__

#include <ext/hash_map>
#include <ext/hash_fun.h>

#define stdext __gnu_cxx
namespace stdext {
/**
        Explicit template specialization of hash of a string class,
        which just uses the internal char* representation as a wrapper.
 */
template <>
struct hash<std::string> {
        size_t operator() (const std::string& x) const {
                return hash<const char*>()(x.c_str());
	// hash<const char*> already exists
        }
};
}

#else

#include <hash_map>

#endif

// boost library headers
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/scoped_array.hpp> 
#include <boost/weak_ptr.hpp>
#include <boost/format.hpp>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include <boost/algorithm/string.hpp>

// headers of other libraries
#include <gsl/gsl_sf.h>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_sys.h>
//#include <gmp.h>
//#include <gmpxx.h>
#include <yaml.h>


//#include "../lib/mpfr/Win32/Release/mpfr.h"

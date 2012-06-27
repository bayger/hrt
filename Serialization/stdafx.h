// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//


#pragma once


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers


#include <memory>	// for auto_ptr
#include <cassert>  // for assert
#include <algorithm>
#include <vector>
#include <hash_map>
#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/scoped_array.hpp>

// 3rd party headers
#include <FreeImage.h>
#include <yaml.h>

// Hrt-Core
#include "../Core/HrtDeps.h"
#include "../Core/HrtCore.h"

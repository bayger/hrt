// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.                   
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif						

#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#endif


#ifdef __GNUG__
#define _TCHAR char
#define TCHAR _TCHAR
#else
#include <tchar.h>
#endif



// TODO: reference additional headers your program requires here
#include <boost/program_options.hpp>
#include "../Core/HrtDeps.h"
#include <fstream>

using namespace boost;
namespace po = boost::program_options;

#undef LoadImage
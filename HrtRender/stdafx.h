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

#include "../Core/HrtDeps.h"
#include <fstream>
#include <boost/program_options.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/time_clock.hpp>
#include <boost/date_time/microsec_time_clock.hpp>
#include <boost/timer.hpp>
#include <FreeImage.h>
#include <SDL.h>

using namespace boost;
namespace po = boost::program_options;

#undef LoadImage
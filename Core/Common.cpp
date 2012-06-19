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
#include "Common.h"

namespace Hrt
{
#define VERSION(major,minor,rel) ((uint) (major << 16) + (minor << 8) + rel );

	
	uint LibraryInfo::GetVersion()
	{
		return VERSION(0,2,4);
	}

	std::string LibraryInfo::GetFullName()
	{
		uint version = GetVersion();
		return str( format("H-RayTracer v%1%.%2%.%3%") % (version >> 16) 
			% ((version >> 8) & 0xff) 
			% (version & 0xff) );
	}
	
	bool LibraryInfo::IsUsingFloats()
	{
#ifdef HRT_USE_FLOATS
		return true;
#else
		return false;
#endif
	}

	bool LibraryInfo::IsUsingRGBColor()
	{
#ifdef HRT_USE_RGB
		return true;
#else
		return false;
#endif
	}


}

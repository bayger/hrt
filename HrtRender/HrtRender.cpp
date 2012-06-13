/*
H-RT Renderer - a command-line raytracing renderer.
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
#include "Program.h"

#undef main
int main(int argc, char* argv[])
{
	Program program;

#ifdef WIN32
	SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);
#endif

  try
  {
	  if (program.Initialize(argc, argv))
	  {
		  program.Run();
		  return 0;
	  }
  }
  catch (Hrt::Exception& ex)
  {
    std::cout << ex.GetMessageA() << std::endl;
  }

	return 1;
}


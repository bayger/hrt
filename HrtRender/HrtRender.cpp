// HrtRender.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Program.h"

#undef main
int main(int argc, char* argv[])
{
	Program program;

#ifdef WIN32
	SetPriorityClass(GetCurrentProcess(), BELOW_NORMAL_PRIORITY_CLASS);
#endif

	if (program.Initialize(argc, argv))
	{
		program.Run();
		return 0;
	}

	return 1;
}


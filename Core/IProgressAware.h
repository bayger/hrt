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
#include "Common.h"

namespace Hrt
{
	/// Interface for classes that can provide progress info about
	/// work they do.
	class IProgressAware
	{
		/// Gets the number representing progress of current stage.
		virtual number GetProgressValue() const =0;

		/// Gets the number representing 100% progress of current stage.
		virtual number GetProgressMax() const =0;

		/// Gets current stage number.
		virtual unsigned int GetCurrentStage() const =0;

		/// Gets the total number of stages.
		virtual unsigned int GetStageCount() const =0;

		/// Gets the name of current stage.
		virtual const std::string& GetStageName() const =0;
	};

}

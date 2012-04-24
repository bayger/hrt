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
#pragma once

/// Some useful methods
class Utils
{
public:

	/// Formats time-span expressed in seconds as "XXhr XXmin XXs"
	static std::string SecondsToString(Hrt::number seconds)
	{
		int hours = (int)Hrt::Math::Floor(seconds / 3600);
		int minutes = (int)Hrt::Math::Floor( (seconds - hours*3600) / 60 );
		Hrt::number secs = (seconds - hours*3600 - minutes*60);

		if (hours > 0)
			return str( format("%ihr %imin %.0fs") % hours % minutes % secs );
		else if (minutes > 0)
			return str( format("%imin %.0fs") % minutes % secs );
		else
			return str( format("%.2fs") % secs );
	}

};
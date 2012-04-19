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
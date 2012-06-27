#pragma once
#include "YamlParser.h"

namespace Hrt { namespace Serialization
{

	class SerializationHelper
	{
	public:
		static Vector3D ReadVector3D(YamlParser& parser);
		static Spectrum ReadSpectrum(YamlParser& parser);

	private:
		SerializationHelper();
		~SerializationHelper();
		static void TemperatureToSpectrum(double t, double c, Spectrum& result);
	};

}}
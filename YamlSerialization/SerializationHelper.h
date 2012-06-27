#pragma once
#include "YamlParser.h"

namespace Hrt { namespace Serialization
{

	class SerializationHelper
	{
	public:
		static Vector3D ReadVector3D(IParser& parser);
		static Spectrum ReadSpectrum(IParser& parser);

	private:
		SerializationHelper();
		~SerializationHelper();
		static void TemperatureToSpectrum(double t, double c, Spectrum& result);
	};

}}
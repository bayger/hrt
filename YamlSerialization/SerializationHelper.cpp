#include "stdafx.h"
#include "SerializationHelper.h"

namespace Hrt { namespace Serialization
{
	Hrt::Vector3D SerializationHelper::ReadVector3D( YamlParser& parser )
	{
		number x,y,z;
		std::string vectorString;
		parser.ReadScalar(vectorString);
		
		char_separator<char> separator(" \t");
		tokenizer<char_separator<char> > tokener(vectorString, separator);

		int i = 0;
		tokenizer<char_separator<char> >::iterator token;
		for(token = tokener.begin(); token != tokener.end(); token++)
		{
			double d = strtod((*token).c_str(), NULL);
			if (i == 0) x = num(d);
			else if (i == 1) y = num(d);
			else if (i == 2) z = num(d);
			else throw SerializationException("Unexpected token when parsing vector");
			i++;
		}

		return Vector3D(x, y, z);
	}

	Hrt::Spectrum SerializationHelper::ReadSpectrum( YamlParser& parser )
	{
		Spectrum result;
		std::string vectorString;
		parser.ReadScalar(vectorString);

		if (vectorString.size() > 0 && vectorString[0] == 'L')
		{
			std::vector<std::string> components;
			boost::algorithm::split(components, vectorString, is_any_of(" \t"));
			if (components.size() < 3)
				throw SerializationException("Invalid format of spectrum");
			double t = strtod(components[1].c_str(), NULL);
			double c = strtod(components[2].c_str(), NULL);

			TemperatureToSpectrum(t, c, result);
		}
		else
		{
			char_separator<char> separator(" \t");
			tokenizer<char_separator<char> > tokener(vectorString, separator);

			int i = 0;
			tokenizer<char_separator<char> >::iterator token;
			for(token = tokener.begin(); token != tokener.end(); token++)
			{
				double d = strtod((*token).c_str(), NULL);
				if (i < Spectrum::LambdaCount)
					result[i] = d;
				else throw SerializationException("Unexpected token when parsing spectrum");
				i++;
			}
		}

		return result;
	}

	void SerializationHelper::TemperatureToSpectrum(double t, double c, Spectrum& result)
	{
		const number SpeedOfLight = 299792458; // m/s
		const number PlanckConst = num(6.626068E-34); // J*s
		const number BoltzmanConst = num(1.3806505E-23); // J/K

		std::cout << "L " << t << ", " << c << std::endl;

		for(int i=0; i<Spectrum::LambdaCount; i++)
		{
			number lambda = Spectrum::IndexToLambda(i);
			number x = c * Consts::TwoPi * SpeedOfLight*SpeedOfLight * PlanckConst / Math::Pow(lambda, 5) 
				/ (Math::Exp(PlanckConst*SpeedOfLight / (lambda*BoltzmanConst*t)) - 1);
			result[i] = x;

			std::cout << x << " ";
		}
		std::cout << std::endl;
	}
}}

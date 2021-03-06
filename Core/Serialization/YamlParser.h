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
#include "../Common.h"

namespace Hrt
{
	class IYamlSerializable;

	class YamlParser
	{
	public:
		YamlParser(const std::string& inputString);
		YamlParser(char* buffer, unsigned int length);
		~YamlParser(void);

		const yaml_event_t& CurrentEvent() { return currentEvent; }
		std::string CurrentValue();
		std::string CurrentTag();
		unsigned int CurrentLine();
		unsigned int CurrentColumn();

		bool NextEvent();

		void ReadMappingStart();
		void ReadMappingEnd();
		void ReadScalar();
		void ReadScalar(std::string& outValue);
		void ReadScalar(number& outValue);
		void ReadScalar(unsigned int& outValue);
		void ReadScalar(int& outValue);
		void ReadScalar(bool& outValue);

	private:
		yaml_parser_t parser;
		std::string inputString;
		char* inputBuffer;
		yaml_event_t currentEvent;

		void Initialize(const char* buffer, unsigned int length);
	};

}

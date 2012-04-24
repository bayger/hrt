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
#include "../Exceptions.h"
#include "YamlParser.h"

namespace Hrt
{

	YamlParser::YamlParser(const std::string& inputString)
	{
		this->inputString = inputString;
		Initialize(this->inputString.c_str(), (int)this->inputString.size());
	}

	YamlParser::YamlParser( char* buffer, unsigned int length )
	{
		Initialize(buffer, length);
	}

	YamlParser::~YamlParser(void)
	{
		yaml_parser_delete(&parser);
	}

	void YamlParser::Initialize(const char* buffer, unsigned int length)
	{
		memset(&parser, 0, sizeof(parser));
		memset(&currentEvent, 0, sizeof(currentEvent)); 
		yaml_parser_initialize(&parser);
		yaml_parser_set_input_string(&parser, (unsigned char*)buffer, length);

		NextEvent();
		if (currentEvent.type != YAML_STREAM_START_EVENT)
			throw InvalidOperationException("YAML couldn't initialize parsing.");
		
		NextEvent();
		if (currentEvent.type != YAML_DOCUMENT_START_EVENT)
			throw InvalidOperationException("Expected start of YAML document.");
	}

	bool YamlParser::NextEvent()
	{
		if (!yaml_parser_parse(&parser, &currentEvent))
			throw InvalidOperationException(
			str( format("Error parsing YAML file at (%1%): %2%") %
			parser.problem_offset %
			std::string(parser.problem)));

		return (currentEvent.type != YAML_STREAM_END_EVENT);
	}

	void YamlParser::ReadMappingStart()
	{
		NextEvent();
		if (currentEvent.type != YAML_MAPPING_START_EVENT)
			throw SerializationException("Mapping start expected.");
	}

	void YamlParser::ReadMappingEnd()
	{
		NextEvent();
		if (currentEvent.type != YAML_MAPPING_END_EVENT)
			throw SerializationException("Mapping end expected.");
	}

	void YamlParser::ReadScalar()
	{
		NextEvent();
		if (currentEvent.type != YAML_SCALAR_EVENT)
			throw SerializationException("Scalar expected.");
	}

	void YamlParser::ReadScalar( std::string& outValue )
	{
		ReadScalar();
		std::string utf8String((char*)currentEvent.data.scalar.value);
		//utf8String += (char)0; // make null terminated
		outValue = utf8String; // TODO: <<< null termination inside
	}

	void YamlParser::ReadScalar( number& outValue )
	{
		ReadScalar();
		std::string utf8String((char*)currentEvent.data.scalar.value);
		double d = strtod(utf8String.c_str(), NULL);
		outValue = num(d);
	}

	void YamlParser::ReadScalar( unsigned int& outValue )
	{
		ReadScalar();
		std::string utf8String((char*)currentEvent.data.scalar.value);
		outValue = (unsigned int)strtoul(utf8String.c_str(), NULL, 10);
	}

	void YamlParser::ReadScalar( int& outValue )
	{
		ReadScalar();
		std::string utf8String((char*)currentEvent.data.scalar.value);
		outValue = (int)strtol(utf8String.c_str(), NULL, 10);
	}

	void YamlParser::ReadScalar( bool& outValue )
	{
		ReadScalar();
		std::string utf8String((char*)currentEvent.data.scalar.value);
		if (utf8String == "true")
			outValue = true;
		else
			outValue = false;
	}

	std::string YamlParser::CurrentValue()
	{
		return currentEvent.data.scalar.value != NULL
			? std::string((char*)currentEvent.data.scalar.value)
			: "";
	}

	std::string YamlParser::CurrentTag()
	{
		return currentEvent.data.scalar.tag != NULL
			? std::string((char*)currentEvent.data.scalar.tag+1 /* ommit ! sign */)
			: "";
	}

	unsigned int YamlParser::CurrentLine()
	{
		return parser.mark.line;
	}

	unsigned int YamlParser::CurrentColumn()
	{
		return parser.mark.column;
	}
}

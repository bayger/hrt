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
#include "YamlParser.h"
#include "SerializationContext.h"
#include "Initialize.h"

namespace Hrt { namespace Serialization {

	template<class T>
	class YamlSerializer
	{
	public:
		static shared_ptr<T> LoadFromFile(std::string fileName)
		{
      Initialize();

			shared_ptr<T> obj(new T());
			std::ifstream objFile;

			objFile.open(fileName.c_str());
			objFile.seekg(0, std::ios::end);
			size_t size = objFile.tellg();
			scoped_array<char> buffer(new char[size+1]);
			memset(buffer.get(), 0, size+1);
			objFile.seekg(0, std::ios::beg);
			objFile.read(buffer.get(), (std::streamsize)size);
			CYamlParser parser(buffer.get(), (unsigned int)strlen(buffer.get()));
			Deserialize(parser);

			return obj;
		}

    /// Builds an object using specified YAML parser and serialization context.
    /// \param parser YAML parser to be used as the source
    /// \param context Serialization context which may be useful in deserialization
    virtual void Deserialize(T& obj, YamlParser& parser, SerializationContext& context)
    {
      parser.ReadMappingStart();
      StartDeserialization();

      while(parser.NextEvent())
      {
        switch(parser.CurrentEvent().type)
        {
        case YAML_MAPPING_END_EVENT:
          FinishDeserialization();
          return;

        case YAML_SCALAR_EVENT:
          if (!ProcessYamlScalar(obj, parser, context))
          {
            std::string message = str(format(
              "Unexpected YAML token '%1%' near line %2%, column %3%")
              % parser.CurrentEvent().data.scalar.value % (parser.CurrentLine()+1)
              % (parser.CurrentColumn()+1));
            throw SerializationException(message);
          }
          break;
        }
      }
    }

    /// Executed just before deserialization process. May be used to clean up the object.
    /// Default implementation does nothing.
    virtual void StartDeserialization() { }

    /// Executed just after the deserialization. May be used to initialize the object.
    /// Default implementation does nothing.
    virtual void FinishDeserialization() { }

    /// YAML scalar (tag->value pair) processing method.
    /// \param parser YAML parser to be used as the source
    /// \param context Serialization context which may be useful in deserialization
    /// \return Should return true for success or false for unsupported scalar tag
    virtual bool ProcessYamlScalar(T& obj, YamlParser& parser, SerializationContext& context)=0;

	};

}}
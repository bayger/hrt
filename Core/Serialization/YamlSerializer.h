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

namespace Hrt
{

	template<class T>
	class YamlSerializer
	{
	public:
		static shared_ptr<T> LoadFromFile(std::string fileName)
		{
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
			obj->Deserialize(parser);

			return obj;
		}

		static void SaveToFile(T& t, std::wstring fileName)
		{
			// TODO: code serializer
		}
	};

}
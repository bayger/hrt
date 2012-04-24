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
#include "Serialization/IYamlSerializable.h"

namespace Hrt
{

	/// Base class for all serializable objects that have a name.
	class NamedObject 
		: public IYamlSerializable
	{
	public:
		const std::string& GetName() { return m_name; }
		void SetName(const std::string& name) { m_name = name; }

		// IYamlSerializable Implementation
		virtual bool ProcessYamlScalar(YamlParser& parser, SerializationContext& context);
		virtual void StartDeserialization();

	private:
		std::string m_name;
	};

}

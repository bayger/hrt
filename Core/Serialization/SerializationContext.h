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

	/// Provides services and information needed for serialization process.
	class SerializationContext
	{
	public:
		SerializationContext() {}
		SerializationContext(const std::string& baseDir)
			: m_baseDir(baseDir)
		{}

		const std::string& GetBaseDirectory() const { return m_baseDir; }

	private:
		std::string m_baseDir;

		// TODO: add more serialization common stuff here
	};

}

/*
H-RT Core - the core of the H-RayTracer ray tracing renderer.
Copyright (c) 2006-2010 H-RT Team.

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
#include <string>

namespace Hrt
{

	class Exception
	{
	private:
		std::string m_message;

	public:
		Exception(void) {};
		
		Exception(const std::string& message)
		{
			m_message = message;
		}

		Exception(const char* message)
		{
			m_message = message;
		}

		const std::string& GetMessage()
		{
			return m_message;
		}
	};

	class InvalidArgumentException : public Exception
	{
	public:
		InvalidArgumentException(const std::string& message)
			: Exception(message) {}

		InvalidArgumentException(const char* message)
			: Exception(message) {}
	};

	class InvalidOperationException : public Exception
	{
	public:
		InvalidOperationException(const std::string& message)
			: Exception(message) {}

		InvalidOperationException(const char* message)
			: Exception(message) {}
	};

	class NotImplementedException : public Exception
	{
	public:
		NotImplementedException()
			: Exception("Method is not implemented") {}

		NotImplementedException(const std::string& message)
			: Exception(message) {}

		NotImplementedException(const char* message)
			: Exception(message) {}
	};

	class NotSupportedException : public Exception
	{
	public:
		NotSupportedException()
			: Exception("Method is not Supported") {}

		NotSupportedException(const std::string& message)
			: Exception(message) {}

		NotSupportedException(const char* message)
			: Exception(message) {}
	};

	class SerializationException : public Exception
	{
	public:
		SerializationException()
			: Exception("Method is not implemented") {}

		SerializationException(const std::string& message)
			: Exception(message) {}

		SerializationException(const char* message)
			: Exception(message) {}
	};

}

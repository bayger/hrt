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

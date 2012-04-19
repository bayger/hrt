#include "stdafx.h"
#include "NamedObject.h"

namespace Hrt
{

	bool NamedObject::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "name")
		{
			parser.ReadScalar(m_name);
		}
		else
			return false;

		return true;

	}

	static unsigned int oid = 1;
	void NamedObject::StartDeserialization()
	{
		m_name = str(format("%1%-oid-%2%") % YamlType() % oid);
		oid++;
	}
}

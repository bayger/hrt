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
#include "YamlSerializer.h"

namespace Hrt { namespace Serialization 
{
  template<typename T>
  class Register
  {
  public:
    typedef boost::function<shared_ptr<T> ()> SerializerFactory;

    void AddType(const std::string& typeId, SerializerFactory serializerFactory)
    {
      m_typeMap[typeId] = serializerFactory;
    }

    void RemoveType(const std::string& typeId)
    {
      m_typeMap.erase(m_typeMap.find(typeId));
    }

    shared_ptr<YamlSerializer<T> > GetSerializer(const std::string& typeId)
    {
      return m_typeMap[typeId]();
    }

  private:
    std::hash_map<std::string, SerializerFactory> m_typeMap;
  };

}}

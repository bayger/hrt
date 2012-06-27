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
#include "../YamlSerializer.h"

namespace Hrt { namespace Serialization
{

  class PlaneSerializer
    : public YamlSerializer<Plane>
  {
    virtual bool ProcessYamlScalar(Plane& obj, YamlParser& parser, SerializationContext& context)
    {
      std::string scalarValue = parser.CurrentValue();
      if (scalarValue == "normal")
        obj.Normal = SerializationHelper::ReadVector3D(parser);
      else if (scalarValue == "distance")
        parser.ReadScalar(obj.D);
      else
        return ShapeSerializer::ProcessYamlScalar(parser, context);

      return true;
    }
  };

}}
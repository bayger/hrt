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
#include "OutgoingRadianceModifierSerializer.h"
#include "Checkerboard.h"
#include "RadianceFilter.h"

namespace Hrt
{

  shared_ptr<OutgoingRadianceModifier> OutgoingRadianceModifierSerializer::Deserialize(std::string exactType, 
    YamlParser& parser, 
    SerializationContext& context)
  {
    if (exactType == "checkerboard")
    {
      OutgoingRadianceModifierOwnedPtr modifier(new Checkerboard);
      modifier->Deserialize(parser, context);
      return modifier;
    }
    else if (exactType == "radiance-filter")
    {
      OutgoingRadianceModifierOwnedPtr modifier(new RadianceFilter);
      modifier->Deserialize(parser, context);
      return modifier;
    }

    throw NotSupportedException("Outgoing radiance modifier type not supported");
  }

};

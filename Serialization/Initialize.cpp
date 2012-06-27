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
#include "Metadata.h"
#include "SerializationHelper.h"

namespace Hrt { namespace Serialization 
{
  static bool isInitialized = false;

  static void RegisterBaseClasses()
  {
    RegisterType<NamedObject>("NamedObject");
    RegisterProperty<NamedObject>("Name",
      [](NamedObject& namedObject, IParser& parser) { namedObject.SetName(parser.ReadString()); } );
  }

  static void RegisterShapes()
  {
    // Shape
    RegisterSubtype<Shape, NamedObject>("Shape");

    // Plane
    RegisterSubtype<Plane, Shape>("Plane");
    RegisterProperty<Plane>("Normal", 
      [](Plane& plane, IParser& parser) { plane.SetNormal(SerializationHelper::ReadVector3D(parser)); } );
    RegisterProperty<Plane>("Distance",
      [](Plane& plane, IParser& parser) { plane.SetDistance(parser.ReadNumber()); });

    // Cylinder
    RegisterSubtype<Cylinder, Shape>("Cylinder");
    RegisterProperty<Cylinder>("Radius",
      [](Cylinder& cylinder, IParser& parser) { cylinder.SetRadius(parser.ReadNumber()); });
    RegisterProperty<Cylinder>("Height",
      [](Cylinder& cylinder, IParser& parser) { cylinder.SetHeight(parser.ReadNumber()); });
    RegisterProperty<Cylinder>("Transform",
      [](Cylinder& cylinder, IParser& parser) { cylinder.SetTransform(DeserializeObject<Matrix>(parser)); });

    // Disc
    RegisterSubtype<Disc, Shape>("Disc");
    RegisterProperty<Disc>("Radius",
      [](Disc& disc, IParser& parser) { disc.SetRadius(parser.ReadNumber()); });
    RegisterProperty<Disc>("Transform",
      [](Disc& disc, IParser& parser) { disc.SetTransform(DeserializeObject<Matrix>(parser)); });

    // Sphere
    RegisterSubtype<Sphere, Shape>("Sphere");
    RegisterProperty<Sphere>("Center",
      [](Sphere& sphere, IParser& parser) { sphere.SetCenter(SerializationHelper::ReadVector3D(parser)); });
    RegisterProperty<Sphere>("Radius",
      [](Sphere& sphere, IParser& parser) { sphere.SetRadius(parser.ReadNumber()); });
    RegisterProperty<Sphere>("EmitterPower",
      [](Sphere& sphere, IParser& parser) { sphere.SetPower(SerializationHelper::ReadSpectrum(parser)); } );
    RegisterProperty<Sphere>("EmitterSampler",
      [](Sphere& sphere, IParser& parser) { sphere.SetEmitterSampler(DeserializeSharedObject<Sampler>(parser)); } );
  }

  void Initialize()
  {
    if (isInitialized)
      return;

    // register all serializable types here:
    RegisterBaseClasses();
    RegisterShapes();

    isInitialized = true;
  }

}}
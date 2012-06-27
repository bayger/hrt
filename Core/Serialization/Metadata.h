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

namespace Hrt { namespace Serialization
{
  // NOTE: In templates T is an object type, P is a property type

  template<typename T, typename P>
  void RegisterProperty(const std::string& propertyName,
    boost::function<const P& (T& obj)> getter,
    boost::function<void (T& obj, P& val)> setter);

  template<typename T, typename P>
  const P& GetProperty(const T& obj, const std::string& propertyName);

  template<typename T, typename P>
  void SetProperty(const T& obj, const std::string& propertyName);

}}
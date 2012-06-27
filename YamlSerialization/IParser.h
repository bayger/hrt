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

namespace Hrt { namespace Serialization {

  class IParser
  {
  public:
    virtual void ReadScalar(std::string& outValue)=0;
    virtual void ReadScalar(number& outValue)=0;
    virtual void ReadScalar(unsigned int& outValue)=0;
    virtual void ReadScalar(int& outValue)=0;
    virtual void ReadScalar(bool& outValue)=0;

    std::string ReadString()
    {
      std::string s;
      ReadScalar(s);
      return s;
    }

    number ReadNumber()
    {
      number n;
      ReadScalar(n);
      return n;
    }

    unsigned int ReadUInt()
    {
      unsigned int ui;
      ReadScalar(ui);
      return ui;
    }

    int ReadInt()
    {
      int i;
      ReadScalar(i);
      return i;
    }

    bool ReadBool()
    {
      bool b;
      ReadScalar(b);
      return b;
    }
  };

}}
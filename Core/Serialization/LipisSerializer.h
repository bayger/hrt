/*
 * H-RT Core - the core of the H-RayTracer ray tracing renderer.
 * Copyright (c) Patryk Bajer, H-RT.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#include "../Materials/Lipis.h"

namespace Hrt
{
  class LipisSerializer
  {
  public:
    static void Save(std::string materialSignature, 
      size_t elevationCount,
      size_t azimuthCount,
      std::vector<shared_ptr<Lipis::LipisAngleData>>& angleData);

    static bool Load(std::string materialSignature, 
      size_t elevationCount,
      size_t azimuthCount,
      std::vector<shared_ptr<Lipis::LipisAngleData>>& angleData);

  };
}
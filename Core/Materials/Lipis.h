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
#pragma once
#include "..\Material.h"
#include "ImportanceSampler.h"

namespace Hrt
{
  /// Linearly interpolated precomputed importance sampling
  class Lipis : public ImportanceSampler, public enable_shared_from_this<Lipis>
  {
  public:
    Lipis(void);

    virtual void Precompute(MaterialPtr material);
    virtual Vector3D SampleVector(number* sample, 
      const Vector3D& outgoingDirection, 
      const Vector3D& tangentU, 
      const Vector3D& tangentV, 
      const Vector3D& n, 
      number& pdf, 
      LightingType::Enum& lightingType);
    virtual number GetPdf(const Vector3D& incomingDirection, 
      const Vector3D& outgoingDirection, 
      const Vector3D& tangentU, 
      const Vector3D& tangentV, 
      const Vector3D& n, 
      const LightingType::Enum lightingType);

  private:
    struct LipisAngleData
    {
      number OutgoingAngle;
      number IdealReflectionPdf;
      number IdealReflectionCdf;
      std::vector<number> PdfValues;
      std::vector<number> CdfValues;
    };

    bool isPrecomputed;
    std::vector<shared_ptr<LipisAngleData>> angleData;
  };
}
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
// This is the main include file of the H-RT Core

// base code:
#include "Common.h"
#include "Exceptions.h"
#include "Math.h"
#include "Matrix.h"
#include "Box.h"
#include "Vector3D.h"
#include "CieXyz.h"
#include "Rgba.h"
#include "Exceptions.h"
#include "Image.h"
#include "Spectrum.h"
#include "Light.h"
#include "Shape.h"
#include "RadianceIntegrator.h"
#include "LightIntegrator.h"
#include "Filter.h"
#include "Material.h"
#include "Primitive.h"
#include "Camera.h"
#include "Canvas.h"
#include "Geometry.h"
#include "Scene.h"

// filters:
#include "Filters/BoxFilter.h"
#include "Filters/TriangleFilter.h"
#include "Filters/GaussianFilter.h"
#include "Filters/SincFilter.h"

// geometries:
#include "Geometries/PlainGeometry.h"

// integrators:
#include "Integrators/PathTracingIntegrator.h"
#include "Integrators/DeterministicIntegrator.h"

// lights:
#include "Lights/AreaLight.h"
#include "Lights/PointLight.h"

// materials:
#include "Materials/ASPhong.h"
#include "Materials/SimpleHe.h"
#include "Materials/CookTorrance.h"
#include "Materials/Mirror.h"
#include "Materials/Phong.h"
#include "Materials/Ward.h"

// samplers:
#include "Samplers/ConstSampler.h"
#include "Samplers/LhcSampler.h"
#include "Samplers/RandomSampler.h"
#include "Samplers/StratifiedSampler.h"

// shapes:
#include "Shapes/Cylinder.h"
#include "Shapes/Disc.h"
#include "Shapes/Plane.h"
#include "Shapes/Sphere.h"
#include "Shapes/Triangle.h"

/*
H-RT Core - the core of the H-RayTracer ray tracing renderer.
Copyright (c) 2006-2010 H-RT Team.

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
#include "Common.h"
#include "Vector3D.h"
#include "NamedObject.h"
#include "Shape.h"
#include "RenderingContext.h"

namespace Hrt
{
	struct RayLight;

	/// Base class for all light sources.
	class Light
		: public NamedObject,
			public ISupportsConcurrency
	{
	public:
		Light() {}

		virtual ~Light() {}

		/// Prepares generation of rays to the specified point in world-space.
		/// \param target Target point if world-space.
		/// \param normal Normal vector to the surface.
		virtual void Prepare(const Vector3D& target, const Vector3D& normal, RenderingContext& rc)
		{
			m_target = target;
			m_normal = normal;
		}

    /// Creates a clone of this light.
    virtual shared_ptr<Light> Clone()=0;

		/// Generates a single ray of light from light source.
		/// \param ray Place for result.
		/// \return Returns true if ray has been generated or false if no more rays.
		virtual bool GenerateRayLight(RayLight* ray, number& pdf, RenderingContext& rc)=0;

		/// Returns true if this light generates delta-like impulse. This means
		/// that GenerateRayLight doesn't generate radiance but intensity (which
		/// is dependent on distance. It also means that the light doesn't have
		/// positive finite area (it may be point or infinite area).
		virtual bool IsDeltaLight() const =0;

		/// For area-lights it returns the shape associated with the light
		virtual ShapeOwnedPtr GetEmitterShape() const { return m_emitterShape.lock(); }

		/// Returns true if the light has finite power (area light, point light, etc.)
		virtual bool HasFinitePower() const { return false; }

		/// Returns total power emitted by the light (works only if HasFinitePower() == true).
		virtual Spectrum GetPower() const { return Spectrum::Zero; }

	protected:
		Vector3D m_target;
		Vector3D m_normal;
		weak_ptr<Shape> m_emitterShape;
	};

	/// Reference to const shared-pointer of Light (used as params and returns)
	typedef const shared_ptr<Light>& LightPtr;
	
	/// Shared-pointer of Light (version for owners)
	typedef shared_ptr<Light> LightOwnedPtr;
}

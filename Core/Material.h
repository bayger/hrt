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
#include "NamedObject.h"
#include "RayLight.h"
#include "Intersection.h"
#include "Random.h"
#include "ISupportsConcurrency.h"

namespace Hrt
{
	/// Enum for lighting type
	namespace LightingType
	{
		enum Enum
		{
			Nothing = 0,
			DiffuseOnly = 1,
			SpecularOnly = 2,
			IdealSpecular = 4,
			AllReflection = DiffuseOnly|SpecularOnly,
		};
	}

	/// Abstract class for all materials.
	class Material
		: public NamedObject,
			public ISupportsConcurrency
	{
	public:
		Material() : m_refractionRe(1), m_trasparency(0) {};
		virtual ~Material() {};

		/// Calculate selective BSDF equation.
		virtual Spectrum CalculateBsdf(const RayLight& incomingRay,
			const Intersection& intersection, 
			LightingType::Enum lightingType)=0;

		/// Sample reflected vector using importance sampling
		virtual Vector3D SampleVector(number* sample, const Vector3D& outgoingDirection, const Vector3D& tangentU, const Vector3D& tangentV, const Vector3D& n, number& pdf);

		/// Returns Pdf for given incoming ray and intersection
		virtual number CalculatePdf(const Vector3D& outgoingDirection, const Vector3D& tangentU, const Vector3D& tangentV, 
			const Vector3D& n, const Vector3D& incomingDirection);

		/// Calculates light ray reflected by the surface.
		virtual void CalculateReflectedRay( const RayLight& incomingRay, 
			const Intersection& intersection, RayLight& reflectedRay, 
			bool isInSpecularCone );

		/// Calculates complete BSDF equation.
		Spectrum CalculateBsdf(const RayLight& incomingRay, 
			const Intersection& intersection);

		/// Calculates complete BSDF equation.
		Spectrum CalculateBsdfIdealSpecular(const RayLight& incomingRay, 
			const Intersection& intersection);

		/// Gets the refraction index of this material.
		const Spectrum& GetRefractiveIndex() const { return m_refractionRe; }

		/// Sets the real part of the refraction index.
		void RefractionRe(const Spectrum& val) { m_refractionRe = val; }

		/// Sets the imaginary part of the refraction index.
		void RefractionIm(const Spectrum& val) { m_refractionIm = val; }

		/// Returns true if material is somehow transparent. Opaque materials return FALSE.
		bool IsTransparent() const { return !m_trasparency.IsZero(); }

		/// Gets transparency factor.
		const Spectrum& GetTrasparency() const { return m_trasparency; }

		/// Sets transparency factor.
		void SetTrasparency(const Spectrum& val) 
		{ 
			m_trasparency = val; 
		}

		/// Returns a signature of material (describes material and its properties)
		virtual const std::string GetSignature()=0;

	protected:
		Spectrum m_refractionRe;
		Spectrum m_refractionIm;
		Spectrum m_trasparency;
	};

	/// Reference to const shared-pointer of Material (used as params and returns)
	typedef const shared_ptr<Material>& MaterialPtr;

	/// Shared-pointer of Material (version for owners)
	typedef shared_ptr<Material> MaterialOwnedPtr;
}

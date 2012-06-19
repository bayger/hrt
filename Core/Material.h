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
#include "Common.h"
#include "NamedObject.h"
#include "RayLight.h"
#include "Intersection.h"
#include "Random.h"
#include "ISupportsConcurrency.h"
#include "Modifiers/SpectrumModifier.h"

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

  namespace ImportanceSamplingType
  {
    enum Enum
    {
      Uniform = 0,
      CosineLobe = 1,
      Lipis = 2,    // uses: linearly interpolated precomputed importance sampler
      Spis = 3      // uses: stepped precomputed importance sampler
    };
  }

  class ImportanceSampler;

	/// Abstract class for all materials.
	class Material
		: public NamedObject,
			public ISupportsConcurrency,
      public enable_shared_from_this<Material>
	{
	public:
		Material();;
		virtual ~Material() {};

		/// Calculate selective BRDF equation.
		virtual Spectrum CalculateBrdf(const RayLight& incomingRay,
			const Intersection& intersection, 
			LightingType::Enum lightingType = LightingType::AllReflection)=0;

		/// Sample reflected vector using importance sampling
		virtual Vector3D SampleVector(number* sample, 
      const Vector3D& outgoingDirection, 
      const Vector3D& tangentU, 
      const Vector3D& tangentV, 
      const Vector3D& n, 
      number& pdf, 
      LightingType::Enum& lightingType);

		/// Returns Pdf for given incoming ray and intersection
		virtual number CalculatePdf(const Vector3D& outgoingDirection, 
      const Vector3D& tangentU, 
      const Vector3D& tangentV, 
			const Vector3D& n, 
      const Vector3D& incomingDirectio, 
      const LightingType::Enum lightingType);

    /// Returns true if material is somehow transparent. Opaque materials return false.
		bool IsTransparent() const { return !m_transparency.IsZero(); }

		/// Transparency property
    AUTO_PROPERTY(Spectrum, m_transparency, Transparency);

    /// Refraction index property - real part
    AUTO_PROPERTY(Spectrum, m_refractionRe, RefractionReal);

    /// Refraction index property - imaginary part
    AUTO_PROPERTY(Spectrum, m_refractionIm, RefractionImaginary);

    /// YAML serializer method
    virtual bool ProcessYamlScalar(YamlParser& parser, SerializationContext& context);

		/// Returns a signature of material (describes material and its properties)
		virtual const std::string GetSignature()=0;

    /// Initializes material for usage in rendering
    virtual void Initialize();

	protected:
		Spectrum m_refractionRe;
		Spectrum m_refractionIm;
		Spectrum m_transparency;
    ImportanceSamplingType::Enum m_importanceSamplingType;
    shared_ptr<ImportanceSampler> m_importanceSampler;
	};

	/// Reference to const shared-pointer of Material (used as params and returns)
	typedef const shared_ptr<Material>& MaterialPtr;

	/// Shared-pointer of Material (version for owners)
	typedef shared_ptr<Material> MaterialOwnedPtr;
}

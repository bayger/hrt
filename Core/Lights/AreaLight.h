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
#include "../Common.h"
#include "../Light.h"
#include "../Matrix.h"
#include "../Spectrum.h"
#include "../LightEmitter.h"

namespace Hrt
{
	class Sampler;

	/// Area light for shapes that emits light.
	class AreaLight : public Light
	{
	public:
		AreaLight() {}
		AreaLight(LightEmitterPtr emitter);
    virtual shared_ptr<Light> Clone();

		// Light overrides

		virtual void Prepare(const Vector3D& target, const Vector3D& normal, RenderingContext& rc);

		virtual bool GenerateRayLight(RayLight* ray, number& pdf, RenderingContext& rc);

		virtual bool IsDeltaLight() const { return false; }

		virtual bool HasFinitePower() const { return true; }

		virtual Spectrum GetPower() const { return m_emitter->GetPower(); }

		// ISupportsConcurrency overrides

		virtual void PrepareForConcurrency(size_t numberOfThreads);

		// Properties

		const std::string& GetEmitterName() const { return m_emitterName; }

		void SetEmitter(LightEmitterPtr emitter);
		LightEmitterPtr GetEmitter() { return m_emitter; }

		// IYamlSerializable overrides

		virtual bool ProcessYamlScalar(YamlParser& parser, SerializationContext& context);

		virtual const std::string& YamlType();

	private:
		LightEmitterOwnedPtr m_emitter;
		Vector3D m_targetPosition;
		Vector3D m_targetNormal;
		std::string m_emitterName;
	};

}

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
#include "Serialization/IYamlSerializable.h"
#include "IProgressAware.h"
#include <boost/timer.hpp>

#include "Light.h"
#include "Geometry.h"
#include "Camera.h"
#include "ISupportsConcurrency.h"

namespace Hrt
{
	class Canvas;
	class Sampler;
	class LightIntegrator;

	class Scene : public enable_shared_from_this<Scene>,
		public IYamlSerializable,
		public ISupportsConcurrency
	{
	public:
		Scene();
		~Scene();

		void AddLight(LightPtr light);

		void RemoveLight(LightPtr light);

		uint GetLightCount() const;

		void ClearLights();

		LightPtr GetLight(uint index) const;

		void SetGeometry(GeometryPtr geometry);

		GeometryPtr GetGeometry() const { return m_geometry; }

		void SetCamera(CameraPtr camera);

		CameraPtr GetCamera() const { return m_camera; }

		void SetCanvas(CanvasPtr canvas) { m_canvas = canvas; }

		CanvasPtr GetCanvas() const { return m_canvas; }

		void Prepare();


		// IYamlSerialization Implementation:

		virtual bool ProcessYamlScalar(YamlParser& parser, SerializationContext& context);
		virtual const std::string& YamlType();
		virtual void FinishDeserialization();


		// ISupportsConcurrency

		virtual void PrepareForConcurrency(size_t numberOfThreads);

	private:
		bool m_isRendering;
		std::vector< LightOwnedPtr > m_lights;
		std::vector< PrimitiveOwnedPtr > m_primitives;

		typedef stdext::hash_map<std::string, LightOwnedPtr> NamedLightMap;
		typedef stdext::hash_map<std::string, ShapeOwnedPtr> NamedShapeMap;
		typedef stdext::hash_map<std::string, MaterialOwnedPtr> NamedMaterialMap;

		NamedLightMap m_namedLights;
		NamedShapeMap m_namedShapes;
		NamedMaterialMap m_namedMaterials;

		GeometryOwnedPtr m_geometry;
		CameraOwnedPtr m_camera;
		CanvasOwnedPtr m_canvas;
		number m_progMax;
		number m_progValue;
		boost::timer m_timer;
		number m_renderingTime;
		unsigned int m_currentStage;
		unsigned int m_totalStages;
		std::string m_stageName;

		void DoRender(CanvasPtr canvas, SamplerPtr sampler, const LightIntegrator&
			integrator);
		void DetectEdges(CanvasPtr canvas);

		bool CheckDepth( CanvasPtr canvas, unsigned int x, unsigned int y, number threshold );
		bool CheckColor( CanvasPtr canvas, unsigned int x, unsigned int y, number threshold );
	};

	/// Reference to const shared-pointer of Scene (used as params and returns)
	typedef const shared_ptr<Scene>& ScenePtr;
	
	/// Shared-pointer of Scene (version for owners)
	typedef shared_ptr<Scene> SceneOwnedPtr;
}

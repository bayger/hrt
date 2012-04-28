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
#include "stdafx.h"
#include "Vector3D.h"
#include "Scene.h"
#include "Light.h"
#include "Camera.h"
#include "Canvas.h"
#include "Sampler.h"
#include "Exceptions.h"
#include "Ray.h"
#include "RayLight.h"
#include "Intersection.h"
#include "Geometry.h"
#include "Material.h"
#include "LightIntegrator.h"
#include "CieXyz.h"
#include "Materials/MaterialSerializer.h"
#include "Shapes/ShapeSerializer.h"
#include "Lights/LightSerializer.h"
#include "Lights/AreaLight.h"
#include "Common.h"
#include "Geometries/PlainGeometry.h"

namespace Hrt
{

	Scene::Scene()
		: m_isRendering(false), m_progMax(1), m_progValue(0), m_geometry(new PlainGeometry()),
		m_currentStage(0), m_totalStages(0)
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::AddLight(LightPtr light)
	{
		if (m_isRendering)
			throw new InvalidOperationException("Can't add light during rendering!");

		LightOwnedPtr p(light);
		m_namedLights[light->GetName()] = p;
		m_lights.push_back( p );
	}

	void Scene::RemoveLight(LightPtr light)
	{
		if (m_isRendering)
			throw new InvalidOperationException("Can't remove light during rendering!");

		std::vector< LightOwnedPtr >::iterator it = m_lights.begin();
		std::vector< LightOwnedPtr >::iterator match = find(m_lights.begin(), m_lights.end(), light );

		if (match != m_lights.end())
		{
			m_namedLights.erase(light->GetName());
			m_lights.erase(match);
		}
	}

	uint Scene::GetLightCount() const
	{
		return (uint)m_lights.size();
	}

	LightPtr Scene::GetLight(uint index) const
	{
		return m_lights[index];
	}

	void Scene::ClearLights()
	{
		if (m_isRendering)
			throw new InvalidOperationException("Can't clear lights during rendering!");

		m_lights.clear();
	}

	void Scene::SetGeometry(GeometryPtr geometry)
	{
		if (m_isRendering)
			throw new InvalidOperationException("Can't set geometry during rendering!");

		m_geometry = geometry;
	}

	void Scene::SetCamera(CameraPtr camera)
	{
		if (m_isRendering)
			throw new InvalidOperationException("Can't set camera during rendering!");

		m_camera = camera;
	}

	bool Scene::CheckDepth( CanvasPtr canvas, unsigned int x, unsigned int y,
		number threshold )
	{
		unsigned int width = canvas->GetWidth();
		unsigned int height = canvas->GetHeight();
		number z22 = canvas->GetDepthValue(x, y);

		number z11 = x > 0 && y > 0 ? canvas->GetDepthValue(x-1, y-1) : z22;
		number z12 = y > 0 ? canvas->GetDepthValue(x, y-1) : z22;
		number z13 = x < width-1 && y > 0 ? canvas->GetDepthValue(x+1, y-1) : z22;
		number z21 = x > 0 ? canvas->GetDepthValue(x-1, y) : z22;
		number z23 = x < width-1 ? canvas->GetDepthValue(x+1, y) : z22;
		number z31 = x > 0 && y < height-1 ? canvas->GetDepthValue(x-1, y+1) : z22;
		number z32 = y < height-1 ? canvas->GetDepthValue(x, y+1) : z22;
		number z33 = x < width-1 && y < height-1 ? canvas->GetDepthValue(x+1, y+1) : z22;


		number zMin = Math::Min(z11, z12, Math::Min(z13, z21,
			Math::Min(z23, z31, Math::Min(z32, z33))));
		number zMax = Math::Max(z11, z12, Math::Max(z13, z21,
			Math::Max(z23, z31, Math::Max(z32, z33))));

		if (Math::Abs(z22 - zMin) > threshold)
			return true;
		else if (Math::Abs(z22 - zMax) > threshold)
			return true;

		return false;
	}

	bool Scene::CheckColor( CanvasPtr canvas, unsigned int x, unsigned int y,
		number threshold )
	{
		unsigned int width = canvas->GetWidth();
		unsigned int height = canvas->GetHeight();
		number c22 = canvas->GetImageValue(x, y).Lumi();

		number c11 = x > 0 && y > 0 ? canvas->GetImageValue(x-1, y-1).Lumi() : c22;
		number c12 = y > 0 ? canvas->GetImageValue(x, y-1).Lumi() : c22;
		number c13 = x < width-1 && y > 0 ? canvas->GetImageValue(x+1, y-1).Lumi() : c22;
		number c21 = x > 0 ? canvas->GetImageValue(x-1, y).Lumi() : c22;
		number c23 = x < width-1 ? canvas->GetImageValue(x+1, y).Lumi() : c22;
		number c31 = x > 0 && y < height-1 ? canvas->GetImageValue(x-1, y+1).Lumi() : c22;
		number c32 = y < height-1 ? canvas->GetImageValue(x, y+1).Lumi() : c22;
		number c33 = x < width-1 && y < height-1 ? canvas->GetImageValue(x+1, y+1).Lumi() : c22;

		// sobel
		//number gx = c11 - c13 + 2*(c21 - c23) + c31 - c33;
		//number gy = c11 + 2*c12 + c13 - c31 - 2*c32 - c33;
		//number g = Math::Sqrt(gx*gx + gy*gy);

		number x22 = (c21 + c23) / 2;
		number y22 = (c12 + c32) / 2;

		return (Math::Abs((x22-c22)/x22) > threshold
			|| Math::Abs((y22-c22)/y22) > threshold);
	}

	void Scene::Prepare()
	{
		m_geometry->Clear();
		PrimitiveOwnedPtr primitive;
		BOOST_FOREACH(primitive, m_primitives)
    {
			m_geometry->AddPrimitive(primitive);
      primitive->GetMaterial()->Initialize();
    }

		m_geometry->Preprocess();
		m_camera->SetCanvas(m_canvas);
	}


	// IYamlSerializable

	bool Scene::ProcessYamlScalar( YamlParser& parser, SerializationContext& context )
	{
		std::string scalarValue = parser.CurrentValue();
		if (scalarValue == "camera")
		{
			CameraOwnedPtr camera(new Camera());
			camera->Deserialize(parser, context);
			this->m_camera = camera;
		}
		else if (scalarValue == "canvas")
		{
			CanvasOwnedPtr canvas(new Canvas());
			canvas->Deserialize(parser, context);
			this->m_canvas = canvas;
		}
		else if (scalarValue == "light")
		{
			std::string scalarType = parser.CurrentTag();
			LightOwnedPtr light = Singleton<LightSerializer>::Instance()
				.Deserialize(scalarType, parser, context);

			shared_ptr<AreaLight> areaLight = dynamic_pointer_cast<AreaLight>(light);
			shared_ptr<Shape> shape = dynamic_pointer_cast<Shape>(light);
			if (areaLight != 0)
			{
				ShapeOwnedPtr shapeEmitter = m_namedShapes[areaLight->GetEmitterName()];
				LightEmitterOwnedPtr emitter = dynamic_pointer_cast<LightEmitter>(shapeEmitter);
				if (emitter == 0)
					throw SerializationException("Invalid shape for area light. Shape must be a light emitter.");
				areaLight->SetEmitter(emitter);

				PrimitiveOwnedPtr luminaire(new Primitive(shapeEmitter, MaterialOwnedPtr()));
				m_primitives.push_back(luminaire);
			}

			AddLight(light);
		}
		else if (scalarValue == "material")
		{
			std::string scalarType = parser.CurrentTag();
			MaterialOwnedPtr material = Singleton<MaterialSerializer>::Instance()
				.Deserialize(scalarType, parser, context);
			m_namedMaterials[material->GetName()] = material;
		}
		else if (scalarValue == "shape")
		{
			std::string scalarType = parser.CurrentTag();
			ShapeOwnedPtr shape = Singleton<ShapeSerializer>::Instance()
				.Deserialize(scalarType, parser, context);
			m_namedShapes[shape->GetName()] = shape;
		}
		else if (scalarValue == "primitive")
		{
			PrimitiveOwnedPtr primitive(new Primitive());
			primitive->Deserialize(parser, context);
			primitive->Initialize(m_namedShapes[primitive->GetShapeName()],
				m_namedMaterials[primitive->GetMaterialName()]);
			m_primitives.push_back(primitive);
		}
		else
			return false;

		return true;
	}

	static std::string yamlType("scene");
	const std::string& Scene::YamlType()
	{
		return yamlType;
	}

	void Scene::FinishDeserialization()
	{
		Prepare();
	}

	void Scene::PrepareForConcurrency(size_t numberOfThreads)
	{
		ISupportsConcurrency::PrepareForConcurrency(numberOfThreads);

		// iterate over all elements of the scene and prepare each one for concurrency
		for(NamedMaterialMap::iterator kv = m_namedMaterials.begin(); kv != m_namedMaterials.end(); kv++)
		{
			kv->second->PrepareForConcurrency(numberOfThreads);
		}

		for(NamedShapeMap::iterator kv = m_namedShapes.begin(); kv != m_namedShapes.end(); kv++)
		{
			kv->second->PrepareForConcurrency(numberOfThreads);
		}

		for(NamedLightMap::iterator kv = m_namedLights.begin(); kv != m_namedLights.end(); kv++)
		{
			kv->second->PrepareForConcurrency(numberOfThreads);
		}
	}

  Hrt::MaterialPtr Scene::GetMaterial(const std::string& name)
  {
    return m_namedMaterials[name];
  }

  NamedMaterialMap& Scene::GetAllMaterials()
  {
    return m_namedMaterials;
  }



}

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
#include "Shape.h"
#include "Material.h"
#include "NamedObject.h"

namespace Hrt
{
	/// Geometry primitive object. Primitive is a shape with associated material.
	class Primitive
		: public NamedObject
	{
	public:
		Primitive();
		Primitive(ShapePtr shape, MaterialPtr material);

		void Initialize(ShapePtr shape, MaterialPtr material);

		ShapePtr GetShape() const { return m_shape; }
		const std::string& GetShapeName() const { return m_shapeName; }

		MaterialPtr GetMaterial() const { return m_material; }
		const std::string& GetMaterialName() const { return m_materialName; }

		// IYamlSerializable Implementation
		virtual bool ProcessYamlScalar(YamlParser& parser, SerializationContext& context);
		virtual const std::string& YamlType();

	private:
		ShapeOwnedPtr m_shape;
		MaterialOwnedPtr m_material;
		std::string m_shapeName;
		std::string m_materialName;
	};

	/// Reference to const shared-pointer of Primitive (used as params and returns)
	typedef const shared_ptr<Primitive>& PrimitivePtr;
	
	/// Shared-pointer of Primitive (version for owners)
	typedef shared_ptr<Primitive> PrimitiveOwnedPtr;
}

#pragma once
#include <iostream>
#include "Renderer/renderer.h"



Renderer::Renderer(Centauri * c) :
		_main(c) {
	//just a quick sample render for testing.

	const Magnum::Trade::MeshData3D cube = Magnum::Primitives::Cube::solid();
	_vertexBuffer.setData(Magnum::MeshTools::interleave(cube.positions(0), cube.normals(0)), Magnum::BufferUsage::StaticDraw);
	Magnum::Containers::Array<char> indexData;
	Magnum::Mesh::IndexType indexType;
	Magnum::UnsignedInt indexStart, indexEnd;
	std::tie(indexData, indexType, indexStart, indexEnd) = Magnum::MeshTools::compressIndices(cube.indices());
	_indexBuffer.setData(indexData, Magnum::BufferUsage::StaticDraw);

    _mesh.setPrimitive(cube.primitive())
        .setCount(cube.indices().size())
        .addVertexBuffer(_vertexBuffer, 0, Magnum::Shaders::Phong::Position{}, Magnum::Shaders::Phong::Normal{})
        .setIndexBuffer(_indexBuffer, 0, indexType, indexStart, indexEnd);

    _transformation = Magnum::Matrix4::rotationX(10.0_degf)*
    		Magnum::Matrix4::rotationY(20.0_degf);
    _color = Magnum::Color3::fromHSV(225.0_degf, 1.0f, 1.0f);

    _projection = Magnum::Matrix4::perspectiveProjection(35.0_degf, Magnum::Vector2{Magnum::defaultFramebuffer.viewport().size()}.aspectRatio(), 0.01f, 100.0f)*
    		Magnum::Matrix4::translation(Magnum::Vector3::zAxis(-10.0f));
}

void Renderer::drawEvent() {
//	for (auto it = _elements.begin(); it != _elements.end(); ++it) {
//		(*it)->drawEvent();
//	}

    _shader.setLightPosition({7.0f, 5.0f, 2.5f})
        .setLightColor(Magnum::Color3{1.0f})
        .setDiffuseColor(_color)
		.setShininess(40.0f)
        .setAmbientColor(Magnum::Color3::fromHSV(_color.hue(), 1.0f, 0.3f))
        .setTransformationMatrix(_transformation)
        .setNormalMatrix(_transformation.rotationScaling())
        .setProjectionMatrix(_projection);
    _mesh.draw(_shader);
}

Renderer::~Renderer(){

}

#pragma once
#ifndef m_renderer_H
#define m_renderer_H

#include <vector>
#include <cstdint>
#include <Corrade/PluginManager/Manager.h>
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Buffer.h>
#include <Magnum/Renderer.h>
#include <Magnum/MeshTools/Interleave.h>
#include <Magnum/MeshTools/CompressIndices.h>
#include <Magnum/Primitives/Cube.h>
#include <Magnum/Shaders/Phong.h>
#include <Magnum/Trade/MeshData3D.h>
#include "ChakraCore.h"


class Centauri;

using namespace Magnum::Math::Literals;
class Renderer {
public:
	Renderer(Centauri *);
	void drawEvent();
	~Renderer();

private:
	Centauri* _main;
	Magnum::Buffer _indexBuffer, _vertexBuffer;
	Magnum::Mesh _mesh;
	Magnum::Shaders::Phong _shader;
	Magnum::Matrix4 _transformation, _projection;
	Magnum::Vector2i _previousMousePosition;
	Magnum::Color3 _color;
};

#endif

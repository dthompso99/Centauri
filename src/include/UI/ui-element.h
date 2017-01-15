#pragma once
#ifndef m_uielement_H
#define m_uielement_H

#include <vector>
#include <string>
#include <memory>
#include <Magnum/Buffer.h>
#include <Magnum/Mesh.h>
#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Math/Vector3.h>
#include <Magnum/Shaders/VertexColor.h>
#include <Magnum/Text/Renderer.h>
#include <Magnum/Shaders/DistanceFieldVector.h>

#include "configure.h"

class Ui;

class DrawableUi {
public:
	static enum RenderType {MESH=0, TEXT=1};
	DrawableUi(int m): renderMethod(0){};
	Magnum::Buffer buffer, indexes;
	Magnum::Mesh mesh;
	Magnum::Shaders::VertexColor3D shader;
	Magnum::Shaders::DistanceFieldVector2D textShader;
	std::unique_ptr<Magnum::Text::Renderer2D> text;
	Magnum::Matrix3 transformation;
	Magnum::Matrix3 projection;
	~DrawableUi(){};
	int renderMethod;

};

class UiElement {
public:
	//UiElement(Ui*);
	void drawEvent();
	void test();
	//~UiElement();
	float w = 0.5f;
	float h = 0.05f;
	float x =-0.5f;
	float y=-0.5f;

protected:
	std::vector<DrawableUi*> _drawables;
	Ui* _ui;
};



#endif

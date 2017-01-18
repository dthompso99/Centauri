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
#include <Magnum/Platform/GlfwApplication.h>

#include "UI/font-container.h"
#include "configure.h"
#include "ChakraCore.h"

class Ui;

class DrawableUi {
public:
	static enum RenderType {
		MESH = 0, TEXT = 1
	};
	DrawableUi(int m) :
			renderMethod(m) {
	}
	;
	Magnum::Buffer buffer, indexes;
	Magnum::Mesh mesh;
	Magnum::Shaders::VertexColor3D shader;

	Magnum::Shaders::DistanceFieldVector2D textShader;
	std::unique_ptr<Magnum::Text::Renderer2D> text;
	Magnum::Matrix3 transformation;
	Magnum::Matrix3 projection;
	FontContainer* fontContainer;
	~DrawableUi() {
	}
	;
	int renderMethod;

};

class UiElement {
public:
	void drawEvent();
	float w = 0.5f;
	float h = 0.07f;
	float x = 0.5f;
	float y = 0.5f;
	bool acceptsKeyboard = false;
	bool keyboardActive = false;
	std::string text = "Test Text";
	std::string type = "Element";
	virtual void onKeyPress(Magnum::Platform::Application::KeyEvent& event){};
	virtual bool onClick(Magnum::Platform::Application::MouseEvent::Button button){return false;};
	virtual void render(){};
	void setPosition(float x, float y);
	static JsValueRef CALLBACK JSsetPosition(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);

	void setSize(float x, float y);
	static JsValueRef CALLBACK JSsetSize(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);

protected:
	std::vector<DrawableUi*> _drawables;
	Ui* _ui;
};

#endif

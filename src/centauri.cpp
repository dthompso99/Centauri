#pragma once
#include "centauri.h"
#include <iostream>

#include <Magnum/Renderer.h>

Centauri::Centauri(const Arguments& arguments) :
		Magnum::Platform::Application { arguments, Configuration { }.setWindowFlags(Magnum::Platform::GlfwApplication::Configuration::WindowFlag::Resizeable) } {
//			Magnum::Platform::GlfwApplication::Configuration::setWindowFlags(WindowFlag::Resizeable);
	Net::Instance()->init();
	_ui = new Ui(this);
	_renderer = new Renderer(this);
	Magnum::Renderer::enable(Magnum::Renderer::Feature::Blending);
	Magnum::Renderer::setBlendFunction(Magnum::Renderer::BlendFunction::SourceAlpha, Magnum::Renderer::BlendFunction::OneMinusSourceAlpha);
	Magnum::Renderer::setBlendEquation(Magnum::Renderer::BlendEquation::Add, Magnum::Renderer::BlendEquation::Add);

}

void Centauri::drawEvent() {
	Net::Instance()->get()->poll();
	Magnum::defaultFramebuffer.clear(Magnum::FramebufferClear::Color);
	_renderer->drawEvent();
	_ui->drawEvent();

	swapBuffers();
}

void Centauri::mousePressEvent(MouseEvent& event) {
	_ui->mousePressEvent(event, mouse_pos);
}
void Centauri::mouseMoveEvent(MouseMoveEvent & event) {
	mouse_pos = (Magnum::Vector2{event.position()} / Magnum::Vector2 { Magnum::defaultFramebuffer.viewport().size() } - Magnum::Vector2 { 0.5f, 0.5f })*Magnum::Vector2 { 2.0f, -2.0f } ;
}

void Centauri::keyPressEvent(KeyEvent & event){
	_ui->keyPressEvent(event);
}

MAGNUM_APPLICATION_MAIN(Centauri)

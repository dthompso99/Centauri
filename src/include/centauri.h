#pragma once
#ifndef m_centauri_H
#define m_centauri_H

#include <Magnum/DefaultFramebuffer.h>
#include <Magnum/Platform/GlfwApplication.h>
#include "UI/ui.h"
#include "Renderer/renderer.h"

class Centauri: public Magnum::Platform::Application {
public:
	explicit Centauri(const Arguments& arguments);

private:
	void drawEvent() override;
	void mousePressEvent(MouseEvent& event) override;
	void mouseMoveEvent(MouseMoveEvent & event) override;
	//void mouseReleaseEvent(MouseEvent& event) override;
	Ui* _ui;
	Magnum::Vector2 mouse_pos;
	Renderer* _renderer;
};

#endif

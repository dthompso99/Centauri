#pragma once
#include "centauri.h"
#include <iostream>

Centauri::Centauri(const Arguments& arguments) :
		Magnum::Platform::Application { arguments } {
	/* TODO: Add your initialization code here */
	_ui = new Ui(this);
}

void Centauri::drawEvent() {
	Magnum::defaultFramebuffer.clear(Magnum::FramebufferClear::Color);
	_ui->drawEvent();
	/* TODO: Add your drawing code here */

	swapBuffers();
}

void Centauri::mousePressEvent(MouseEvent& event) {
	std::cout << "MousePressEvent " << std::endl;
}

MAGNUM_APPLICATION_MAIN(Centauri)

#pragma once
#include "Renderer/renderer.h"
#include <iostream>


Renderer::Renderer(Centauri * c) :
		_main(c) {
//	_elements.push_back(new InputBox(this));
}

void Renderer::drawEvent() {
//	for (auto it = _elements.begin(); it != _elements.end(); ++it) {
//		(*it)->drawEvent();
//	}
}

Renderer::~Renderer(){

}

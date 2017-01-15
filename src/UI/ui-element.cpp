#pragma once
#include "UI/ui-element.h"
#include <iostream>

//UiElement::UiElement(Ui* u): _ui(u){
//
//}
void UiElement::drawEvent() {
//	/_mesh.draw(_shader);
	for (auto it = _drawables.begin(); it != _drawables.end(); ++it) {
		if ((*it)->renderMethod == 0) {
			(*it)->mesh.draw((*it)->shader);
		} else if ((*it)->renderMethod == 1) {
			//(*it)->textShader.setVectorTexture(_ui->_cache.texture())
			(*it)->text->mesh().draw((*it)->textShader);
		}
	}
}
void UiElement::test() {
	std::cout << "Draw Event from Element " << std::endl;
}
//UiElement::~UiElement(){
//
//}

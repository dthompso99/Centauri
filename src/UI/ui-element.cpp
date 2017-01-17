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
			(*it)->textShader.setVectorTexture((*it)->fontContainer->cache.texture());
			(*it)->textShader.setTransformationProjectionMatrix((*it)->projection * (*it)->transformation);
//		        .setColor(Magnum::Color3{1.0f})
//		        .setSmoothness(0.75f);
			(*it)->text->render(text);
			(*it)->text->mesh().draw((*it)->textShader);
		}
	}
}


//UiElement::~UiElement(){
//
//}

#pragma once
#include "UI/ui-element.h"
#include <iostream>

void UiElement::drawEvent() {
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

void UiElement::setPosition(float newx, float newy) {
	x = newx;
	y = newy;
	render();
}

JsValueRef CALLBACK UiElement::JSsetPosition(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount,
		void *callbackState) {
	JsValueRef output = JS_INVALID_REFERENCE;
	void* ref;
	JsGetExternalData(arguments[0], &ref);
	double x = 0;
	JsNumberToDouble(arguments[1], &x);
	double y = 0;
	JsNumberToDouble(arguments[2], &y);
	static_cast<UiElement*>(ref)->setPosition(x, y);
	return output;
}

void UiElement::setSize(float newx, float newy) {
	w = newx;
	h = newy;
	render();
}

JsValueRef CALLBACK UiElement::JSsetSize(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount,
		void *callbackState) {
	JsValueRef output = JS_INVALID_REFERENCE;
	void* ref;
	JsGetExternalData(arguments[0], &ref);
	double x = 0;
	JsNumberToDouble(arguments[1], &x);
	double y = 0;
	JsNumberToDouble(arguments[2], &y);
	static_cast<UiElement*>(ref)->setSize(x, y);
	return output;
}

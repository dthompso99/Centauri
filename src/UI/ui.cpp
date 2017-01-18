#pragma once
#include "UI/ui.h"
#include <iostream>
#include "configure.h"
#include <Magnum/Text/Renderer.h>
#include "jsbinding.h"
#include "centauri.h"



void CALLBACK PromiseContinuationCallback(JsValueRef task, void *callbackState)
{
	JsValueRef global;
	JsGetGlobalObject(&global);
	std::queue<Task*> * q = (std::queue<Task*> *)callbackState;
	q->push(new Task(task, 0, global, JS_INVALID_REFERENCE));
}
Ui* Ui::global_ui = NULL;
JsValueRef Ui::JSUiObjectPrototype;

Ui::Ui(Centauri * c) :
		_main(c), _manager(MAGNUM_PLUGINS_FONT_DIR) {
	global_ui = this;


	//init javascript context
	JsContextRef context;
	JsValueRef result;
	currentSourceContext = 0;

	JsCreateRuntime(JsRuntimeAttributeNone, nullptr, &runtime);
	JsCreateContext(runtime, &context);
	JsSetCurrentContext(context);

	if (JsSetPromiseContinuationCallback(PromiseContinuationCallback, &taskQueue) != JsNoError)
		throw "failed to set PromiseContinuationCallback.";

	Ui::host = this;
	addGlobalBinding();
	addUiJsBindings();

	Magnum::Utility::Resource rs("fonts");
	std::string script = rs.get("ui.js");

	if (JsRunScript(std::wstring(script.begin(), script.end()).c_str(), currentSourceContext++, L"", &result) != JsNoError)
		throw "failed to execute script.";

}
void Ui::addElement(UiElement* e){
	_elements.push_back(e);
}

void Ui::drawEvent() {
	jsLoop();

	for (auto it = _elements.begin(); it != _elements.end(); ++it) {
		(*it)->drawEvent();
	}
}

void Ui::mousePressEvent(Magnum::Platform::Application::MouseEvent& event, Magnum::Vector2 press) {
	setAllInactive();
	for (auto it = _elements.begin(); it != _elements.end(); ++it) {
		std::cout << "mouse: " << std::to_string(press.x()) << ", " << std::to_string(press.y()) << std::endl;
		std::cout << "element: " << std::to_string((*it)->x) << ", " << std::to_string((*it)->y) << std::endl;
		if (press.x() >= (*it)->x && press.x() <= (*it)->x + (*it)->w && press.y() >= (*it)->y && press.y() <= (*it)->y + (*it)->h) {
			event.setAccepted((*it)->onClick(event.button()));
		}
	}
}
void Ui::setAllInactive(){
	for (auto it = _elements.begin(); it != _elements.end(); ++it) {
		(*it)->keyboardActive = false;
	}
}
void Ui::keyPressEvent(Magnum::Platform::Application::KeyEvent & event){
	std::cout << "Keypress: " << event.keyName() << std::endl;
	for (auto it = _elements.begin(); it != _elements.end(); ++it) {
		if ((*it)->keyboardActive) {
			(*it)->onKeyPress(event);
		}
	}
}

FontContainer* Ui::loadFont(std::string fontName, float fontSize) {
	std::string key = fontName + "_" + std::to_string(fontSize);
	if (_fonts.find(key) == _fonts.end()) {
		_fonts[key] = new FontContainer(_manager.loadAndInstantiate("FreeTypeFont"));
		if (!_fonts[key]) {
			std::cout << "FreeTypeFont Not loaded" << std::endl;
		} else {
			Magnum::Utility::Resource rs("fonts");
			if (!_fonts[key]->font->openSingleData(rs.getRaw(fontName), fontSize)) {
				std::cout << fontName << " Not loaded" << std::endl;
			} else {
				std::cout << fontName << " Successfully Loaded" << std::endl;
			}
			_fonts[key]->font->fillGlyphCache(_fonts[key]->cache, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:-+,.!° ");
			return _fonts[key];
		}
	} else {
		return _fonts[key];
	}
}

//JSCreateElement
JsValueRef CALLBACK Ui::JSCreateElement(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount,
		void *callbackState) {
	assert(!isConstructCall && argumentCount == 2 );
	JsValueRef output = JS_INVALID_REFERENCE;
	JsValueRef stringValue;
	JsConvertValueToString(arguments[1], &stringValue);
	const wchar_t *el;
	size_t length;
	JsStringToPointer(stringValue, &el, &length);

	if (wcscmp(el, L"InputBox") == 0) {
		InputBox* e = new InputBox(global_ui);
		JsCreateExternalObject(e, nullptr, &output);
		e->setRefrence(output);
	}
	JsSetPrototype(output, JSUiObjectPrototype);
	return output;
}

JsValueRef CALLBACK Ui::JSAppendChild(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount,
		void *callbackState) {
	assert(!isConstructCall && (argumentCount == 2));
	void* element;
	JsGetExternalData(arguments[1], &element);
//	std::string oType = static_cast<UiElement*>(element)->type;
//	if (oType == "InputBox"){
	global_ui->addElement(static_cast<UiElement*>(element));
//	}
	return arguments[0];
}

void Ui::addUiJsBindings(){
	JsValueRef globalObject;
	JsGetGlobalObject(&globalObject);

	JsValueRef ui;
	JsCreateObject(&ui);
	setProperty(globalObject, L"ui", ui);
	setCallback(ui, L"createElement", JSCreateElement, nullptr);
	setCallback(ui, L"appendChild", JSAppendChild, nullptr);
//	setCallback(ui, L"addEventListener", JSaddEventListener, nullptr);
}

Ui::~Ui() {
	JsSetCurrentContext (JS_INVALID_REFERENCE);
	JsDisposeRuntime(runtime);
}

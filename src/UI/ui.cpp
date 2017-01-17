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

Ui::Ui(Centauri * c) :
		_main(c), _manager(MAGNUM_PLUGINS_FONT_DIR) {

	_elements.push_back(new InputBox(this));

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

//	Net::Instance()->get()->http_get("http://uthertools.thompsoninnovations.com/centauri/ui.js", [](std::string body) {
//		std::cout << "fetched script: " << body << std::endl;
//	}, [](int err) {
//		std::cout << "get error: " << err << std::endl;
//	});
}

void Ui::drawEvent() {
	jsLoop();

	for (auto it = _elements.begin(); it != _elements.end(); ++it) {
		(*it)->drawEvent();
	}
}

void Ui::mousePressEvent(Magnum::Platform::Application::MouseEvent& event, Magnum::Vector2 press) {
	std::cout << "Mouse Event in UI handled" << std::endl;
	for (auto it = _elements.begin(); it != _elements.end(); ++it) {
		std::cout << "mouse: " << std::to_string(press.x()) << ", " << std::to_string(press.y()) << std::endl;
		std::cout << "element: " << std::to_string((*it)->x) << ", " << std::to_string((*it)->y) << std::endl;
		if (press.x() >= (*it)->x && press.x() <= (*it)->x + (*it)->w && press.y() >= (*it)->y && press.y() <= (*it)->y + (*it)->h) {
			std::cout << "Handle Event!" << std::endl;
//				return true;
			(*it)->text = "Clicked!";
			event.setAccepted((*it)->onClick(event.button()));
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

void Ui::addUiJsBindings(){

}

Ui::~Ui() {
	JsSetCurrentContext (JS_INVALID_REFERENCE);
	JsDisposeRuntime(runtime);
}

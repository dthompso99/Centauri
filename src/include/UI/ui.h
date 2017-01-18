#pragma once
#ifndef m_ui_H
#define m_ui_H

//#include "centauri.h"
#include <vector>
#include <cstdint>
#include <queue>
#include <Magnum/Platform/GlfwApplication.h>
#include <Corrade/PluginManager/Manager.h>

#include "ChakraCore.h"
#include "Task.h"
#include "jsbinding.h"
#include "UI/input-box.h"
#include "UI/font-container.h"
#include "TiNetwork/TiNetwork.h"

class Centauri;

class Ui: public JsGlobalBinding {
public:
	Ui(Centauri *);
	void drawEvent();
	void setAllInactive();
	void addElement(UiElement*);
	void mousePressEvent(Magnum::Platform::Application::MouseEvent& event, Magnum::Vector2 loc);
	void keyPressEvent(Magnum::Platform::Application::KeyEvent & event);
	FontContainer* loadFont(std::string, float);
	~Ui();
protected:
	std::vector<UiElement*> _elements;
private:
	Centauri* _main;
	static JsValueRef JSUiObjectPrototype;
	void addUiJsBindings();

	Corrade::PluginManager::Manager<Magnum::Text::AbstractFont> _manager;
	std::map<std::string, FontContainer*> _fonts;

	static JsValueRef CALLBACK JSCreateElement(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);static JsValueRef CALLBACK JSAppendChild(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);
//	static JsValueRef CALLBACK JSaddEventListener(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);

	JsRuntimeHandle runtime;
	unsigned currentSourceContext;
	static Ui* global_ui;
};

#endif

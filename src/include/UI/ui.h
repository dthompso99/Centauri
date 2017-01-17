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

#include "UI/input-box.h"
#include "UI/font-container.h"
#include "TiNetwork/TiNetwork.h"


class Centauri;

class Ui {
public:
	Ui(Centauri *);
	void drawEvent();
	void mousePressEvent(Magnum::Platform::Application::MouseEvent& event, Magnum::Vector2 loc);
	FontContainer* loadFont(std::string, float);
	~Ui();

private:
	Centauri* _main;
	std::vector<UiElement*> _elements;
	Corrade::PluginManager::Manager<Magnum::Text::AbstractFont> _manager;
	std::map<std::string, FontContainer*> _fonts ;
	TiNetwork* t;
	std::queue<Task*> taskQueue;
	JsRuntimeHandle runtime;
	unsigned currentSourceContext;
};

#endif

#pragma once
#ifndef m_ui_H
#define m_ui_H

//#include "centauri.h"
#include <vector>
#include <cstdint>
#include <Corrade/PluginManager/Manager.h>

#include "ChakraCore.h"

#include "UI/input-box.h"
#include "UI/font-container.h"

class Centauri;

class Ui {
public:
	Ui(Centauri *);
	void drawEvent();
	FontContainer* loadFont(std::string, float);
	~Ui();

private:
	Centauri* _main;
	std::vector<UiElement*> _elements;
	Corrade::PluginManager::Manager<Magnum::Text::AbstractFont> _manager;
	std::map<std::string, FontContainer*> _fonts ;

};

#endif

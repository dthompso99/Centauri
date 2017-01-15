#pragma once
#include "UI/ui.h"
#include <iostream>
#include "configure.h"


Ui::Ui(Centauri * c) :
		_main(c), _manager(MAGNUM_PLUGINS_FONT_DIR) {
	_elements.push_back(new InputBox(this));
}

void Ui::drawEvent() {
	for (auto it = _elements.begin(); it != _elements.end(); ++it) {
		(*it)->drawEvent();
	}
}

FontContainer* Ui::loadFont(std::string fontName, float fontSize) {
	if (_fonts.find(fontName) == _fonts.end()) {
		_fonts[fontName] = new FontContainer(_manager.loadAndInstantiate("FreeTypeFont"));
		if (!_fonts[fontName]) {
			std::cout << "FreeTypeFont Not loaded" << std::endl;
		} else {
			Magnum::Utility::Resource rs("fonts");
			if (!_fonts[fontName]->font->openSingleData(rs.getRaw(fontName), fontSize)) {
				std::cout << fontName << " Not loaded" << std::endl;
			} else {
				std::cout << fontName << " Successfully Loaded" << std::endl;
			}
			_fonts[fontName]->font->fillGlyphCache(_fonts[fontName]->cache, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789:-+,.!° ");
			return _fonts[fontName];
		}
	} else {
		return _fonts[fontName];
	}
}

Ui::~Ui() {

}

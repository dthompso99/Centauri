#pragma once
#ifndef m_FontContainer_H
#define m_FontContainer_H

#include <Magnum/Text/AbstractFont.h>
#include <Magnum/Text/DistanceFieldGlyphCache.h>

class FontContainer {
public:
	FontContainer(std::shared_ptr<Magnum::Text::AbstractFont> f): font(f), cache(Magnum::Vector2i(2048), Magnum::Vector2i(512), 22){

	}
	std::shared_ptr<Magnum::Text::AbstractFont> get(){
		return font;
	}
	std::shared_ptr<Magnum::Text::AbstractFont> font;
	~FontContainer();
	Magnum::Text::DistanceFieldGlyphCache cache;
};

#endif

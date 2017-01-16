#pragma once
#ifndef m_renderer_H
#define m_renderer_H

#include <vector>
#include <cstdint>
#include <Corrade/PluginManager/Manager.h>

#include "ChakraCore.h"


class Centauri;

class Renderer {
public:
	Renderer(Centauri *);
	void drawEvent();
	~Renderer();

private:
	Centauri* _main;
};

#endif

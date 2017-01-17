#pragma once
#include <stddef.h>
#include "net.h"

Net* Net::m_pInstance = NULL;

Net* Net::Instance() {
	if (!m_pInstance) {
		m_pInstance = new Net;
	}
	return m_pInstance;
}

void Net::init() {
	_net = new TiNetwork();
}

void Net::poll(){
	_net->poll();
}
TiNetwork* Net::get() {
	return _net;
}

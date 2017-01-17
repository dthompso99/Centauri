#pragma once
#ifndef net_H
#define net_H
#include "TiNetwork/TiNetwork.h"

class Net {
public:
	static Net* Instance();
	void poll();
	void init();
	TiNetwork* get();

private:
	Net(){};
	Net(Net const&){};
	Net& operator=(Net const&){};
	TiNetwork* _net;
	static Net* m_pInstance;
};

#endif

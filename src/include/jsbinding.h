#pragma once
#ifndef m_jsbinding_H
#define m_jsbinding_H
#include <cstdint>
#include <wchar.h>
#include <cassert>
#include <queue>
#include <ctime>
#include "Task.h"
#include "ChakraCore.h"

class JsGlobalBinding {
public:
	static JsGlobalBinding* host;
	void addGlobalBinding();
	void jsLoop();
	static void setProperty(JsValueRef object, const wchar_t *propertyName, JsValueRef property);
	static void setCallback(JsValueRef object, const wchar_t *propertyName, JsNativeFunction callback, void *callbackState);
	std::queue<Task*> taskQueue;
protected:
	static JsValueRef CALLBACK JSLog(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);
	static JsValueRef CALLBACK JSGet(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);
	static JsValueRef CALLBACK JSSetTimeout(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);
	static JsValueRef CALLBACK JSSetInterval(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState);
private:
	static JsValueRef JSUiPrototype;
	static JsValueRef JSUiObjectPrototype;
	static JsValueRef getProperty(JsValueRef object, const wchar_t *propertyName);
};


#endif

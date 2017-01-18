#pragma once

#include "jsbinding.h"
#include "net.h"

JsGlobalBinding* JsGlobalBinding::host;

JsValueRef JsGlobalBinding::JSUiObjectPrototype;

JsValueRef CALLBACK JsGlobalBinding::JSGet(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState) {
	assert(!isConstructCall && argumentCount == 3);
	JsValueRef output = JS_INVALID_REFERENCE;
	JsValueRef func = arguments[2];
	JsValueRef stringValue;
	JsConvertValueToString(arguments[1], &stringValue);
	const wchar_t *wurl;
	size_t length;
	JsStringToPointer(stringValue, &wurl, &length);

	std::wstring wsurl(wurl);

		Net::Instance()->get()->http_get(std::string(wsurl.begin(), wsurl.end()), [func](std::string body) {
			JsValueRef str;
			JsCreateString(body.c_str(), strlen(body.c_str()), &str);
			JsValueRef args[] = {func, str};
			JsValueRef result;
			JsCallFunction(func, args, _countof(args), &result);

		}, [](int err) {
			//todo: figure out how to call the error
		});
		return output;
}

JsValueRef CALLBACK JsGlobalBinding::JSLog(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState) {
	for (unsigned int index = 1; index < argumentCount; index++) {
		if (index > 1) {
			wprintf(L" ");
		}
		JsValueRef stringValue;
		JsConvertValueToString(arguments[index], &stringValue);
		const wchar_t *string;
		size_t length;
		JsStringToPointer(stringValue, &string, &length);
		wprintf(L"ui console: %s", string);
	}
	wprintf(L"\n");
	return JS_INVALID_REFERENCE;
}

JsValueRef CALLBACK JsGlobalBinding::JSSetTimeout(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount, void *callbackState) {
	assert(!isConstructCall && argumentCount == 3);
	JsValueRef func = arguments[1];
	int delay = 0;
	JsNumberToInt(arguments[2], &delay);
	host->taskQueue.push(new Task(func, delay, arguments[0], JS_INVALID_REFERENCE));
	return JS_INVALID_REFERENCE;
}

JsValueRef CALLBACK JsGlobalBinding::JSSetInterval(JsValueRef callee, bool isConstructCall, JsValueRef *arguments, unsigned short argumentCount,
		void *callbackState) {
	assert(!isConstructCall && argumentCount == 3);
	JsValueRef func = arguments[1];
	int delay = 0;
	JsNumberToInt(arguments[2], &delay);
	host->taskQueue.push(new Task(func, delay, arguments[0], JS_INVALID_REFERENCE, true));
	return JS_INVALID_REFERENCE;
}

JsValueRef JsGlobalBinding::getProperty(JsValueRef object, const wchar_t *propertyName) {
	JsValueRef output;
	JsPropertyIdRef propertyId;
	JsGetPropertyIdFromName(propertyName, &propertyId);
	JsGetProperty(object, propertyId, &output);
	return output;
}

void JsGlobalBinding::setProperty(JsValueRef object, const wchar_t *propertyName, JsValueRef property) {
	JsPropertyIdRef propertyId;
	JsGetPropertyIdFromName(propertyName, &propertyId);
	JsSetProperty(object, propertyId, property, true);
}

void JsGlobalBinding::setCallback(JsValueRef object, const wchar_t *propertyName, JsNativeFunction callback, void *callbackState) {
	JsPropertyIdRef propertyId;
	JsGetPropertyIdFromName(propertyName, &propertyId);
	JsValueRef function;
	JsCreateFunction(callback, callbackState, &function);
	JsSetProperty(object, propertyId, function, true);
}


void JsGlobalBinding::addGlobalBinding(){
	JsValueRef globalObject;
	JsGetGlobalObject(&globalObject);
	//console
	JsValueRef console;
	JsCreateObject(&console);
	setProperty(globalObject, L"console", console);
	setCallback(console, L"log", JSLog, nullptr);
	setCallback(console, L"warn", JSLog, nullptr);
	setCallback(console, L"error", JSLog, nullptr);
	//interval and timeout
	setCallback(globalObject, L"setTimeout", JSSetTimeout, nullptr);
	setCallback(globalObject, L"setInterval", JSSetInterval, nullptr);

	//http
	JsValueRef http;
	JsCreateObject(&http);
	setProperty(globalObject, L"http", http);
	setCallback(http, L"get", JSGet, nullptr);
}

void JsGlobalBinding::jsLoop(){
	if (!taskQueue.empty()) {
		Task* task = taskQueue.front();
		taskQueue.pop();
		int currentTime = clock() / (double) (CLOCKS_PER_SEC / 1000);
		if (currentTime - task->_time > task->_delay) {
			task->invoke();
			if (task->_repeat) {
				task->_time = currentTime;
				taskQueue.push(task);
			} else {
				delete task;
			}
		} else {
			taskQueue.push(task);
		}
	}
}

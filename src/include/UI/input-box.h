#pragma once
#ifndef m_inputbox_H
#define m_inputbox_H

#include <string>

#include "UI/ui-element.h"
#include "UI/ui.h"


//class Ui;

class InputBox : public UiElement{
public:
	InputBox(Ui *);
	~InputBox();
	bool onClick(Magnum::Platform::GlfwApplication::MouseEvent::Button button) override;
	void onKeyPress(Magnum::Platform::Application::KeyEvent& event) override;
	void setRefrence(JsValueRef);
	void render();
	std::string type="InputBox";
	bool acceptsKeyboard = true;

protected:
	Ui* _ui;
private:
	JsValueRef jsref;
//	std::unique_ptr<Magnum::Text::Renderer2D> _textObj;
//    std::unique_ptr<Magnum::Text::AbstractFont> _font;
};
#endif

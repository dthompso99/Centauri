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
//	std::string text = "Test Text";
protected:
	Ui* _ui;
private:
//	std::unique_ptr<Magnum::Text::Renderer2D> _textObj;
//    std::unique_ptr<Magnum::Text::AbstractFont> _font;
};
#endif

#pragma once
#include <iostream>
#include "UI/input-box.h"
#include "UI/font-container.h"
#include <Magnum/Text/Renderer.h>


InputBox::InputBox(Ui* u): _ui(u) {

    DrawableUi* background = new DrawableUi(0);
    Magnum::Vector3 data2[] = {
            { float(x), float(y), 0.0f}, {0.2f, 0.2f, 0.2f},
            { float(x+w), float(y), 0.0f}, {0.2f, 0.2f, 0.2f},
			{ float(x), float(y+h), 0.0f}, {0.2f, 0.2f, 0.2f},
    		{ float(x+w), float(y+h), 0.0f}, {0.2f, 0.2f, 0.2f}
    };
    background->buffer.setData(data2, Magnum::BufferUsage::StaticDraw);
    background->mesh.setPrimitive(Magnum::MeshPrimitive::TriangleStrip )
        .setCount(4)
        .addVertexBuffer(background->buffer, 0, Magnum::Shaders::VertexColor3D::Position{}, Magnum::Shaders::VertexColor3D::Color{});
    _drawables.push_back(background);

    Magnum::Vector3 data[] = {
        { float(x), float(y), 0.0f}, {1.0f, 1.0f, 1.0f},
        { float(x+w), float(y), 0.0f}, {1.0f, 1.0f, 1.0f},
		{ float(x+w), float(y+h), 0.0f}, {1.0f, 1.0f, 1.0f},
		{ float(x), float(y+h), 0.0f}, {1.0f, 1.0f, 1.0f}
    };
    DrawableUi* frame = new DrawableUi(0);
    frame->buffer.setData(data, Magnum::BufferUsage::StaticDraw);
    frame->mesh.setPrimitive(Magnum::MeshPrimitive::LineLoop  )
        .setCount(4)
        .addVertexBuffer(frame->buffer, 0, Magnum::Shaders::VertexColor3D::Position{}, Magnum::Shaders::VertexColor3D::Color{});
    _drawables.push_back(frame);

    //FontContainer* f = _ui->loadFont("DejaVuSans.ttf", 110.0f);
    float padding=h * 0.07f;

    DrawableUi* textlayer = new DrawableUi(1);
    textlayer->fontContainer = _ui->loadFont("arial.ttf", 150.0f);
    textlayer->text.reset(new Magnum::Text::Renderer2D(*textlayer->fontContainer->font, textlayer->fontContainer->cache, h-(padding*2), Magnum::Text::Alignment::TopLeft ));
    textlayer->text->reserve(40, Magnum::BufferUsage::DynamicDraw, Magnum::BufferUsage::StaticDraw);
    textlayer->projection = Magnum::Matrix3::translation(Magnum::Vector2(x+padding,y+h-padding));
    textlayer->textShader.setColor(Magnum::Color3{1.0f});
    textlayer->textShader.setSmoothness(0.25f);
    //    textlayer->projection = Magnum::Matrix3::scaling(Magnum::Vector2::yScale(Magnum::Vector2(Magnum::defaultFramebuffer.viewport().size()).aspectRatio()));

//    textlayer->textShader.setTransformationProjectionMatrix(textlayer->projection *
//    		Magnum::Matrix3::translation(1.0f/textlayer->projection.rotationScaling().diagonal()))
//    	.setColor(Magnum::Color3{1.0f})
//		.setSmoothness(0.25f);
    textlayer->textShader.setVectorTexture(textlayer->fontContainer->cache.texture());

    _drawables.push_back(textlayer);
}
bool InputBox::onClick(Magnum::Platform::GlfwApplication::MouseEvent::Button button){
	text = "Clicked!";
	return true;
}
InputBox::~InputBox(){

}

#include "Supernova.h"
#include "Scene.h"

#include "Button.h"
#include "TextEdit.h"
#include "Image.h"
#include "Polygon.h"

#include <string>
#include <sstream>
#include <iostream>

using namespace Supernova;

Scene scene;
Button button(&scene);
TextEdit textedit(&scene);
Image image(&scene);
Text text(&scene);

//Scene scene2;
//Button button2(&scene2);

void onPress();

void init(){
    Engine::setCanvasSize(1000, 480);
    Engine::setCallTouchInMouseEvent(true);

    button.setTexture("button_normal.png");
    button.setTexturePressed("button_disable.png");
    button.setPosition(100, 200, 0);
    button.setSize(400, 400);
    button.setMargin(5);
    //button.setLabelFont("arial.ttf");
    button.setLabel("Button");
    button.setFontSize(80);
    button.setLabelColor(Vector4(0.2, 0.2, 0.2, 1.0));
    button.getComponent<ButtonComponent>().onPress = onPress;

    textedit.setPosition(300, 100, 0);
    textedit.setTexture("textedit.png");
    textedit.setMargin(5);
    textedit.setSize(200, 50);
    textedit.setText("");

    //image.setTexture(&scene2.getFramebuffer());
    image.setTexture("tile.png");
    image.setPosition(550,100,0);
    image.setSize(400,400);

    //scene2.setBackgroundColor(0.5, 0.5, 0.5);
    //scene2.setRenderToTexture(true);

    //button2.setTexture("button_normal.png");
    //button2.setTexturePressed("button_disable.png");
    //button2.setPosition(100, 200, 0);
    //button2.setSize(400, 400);
    //button2.setMargin(5);
    //button2.setLabel("Button2");
    //button2.setFontSize(80);
    //button2.setLabelColor(Vector4(0.2, 0.2, 0.2, 1.0));

    Engine::setScene(&scene);
    //Engine::addSceneLayer(&scene2);

}

void onPress(){
    //text.setText("Eduardo Dória Lima");
    button.setPosition(150, 300, 0);
}
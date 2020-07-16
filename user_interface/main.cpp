#include "Supernova.h"
#include "Scene.h"

#include "Button.h"
#include "TextEdit.h"
#include "Sprite.h"
#include "Texture.h"
#include "Lines.h"
#include "Log.h"
#include "FileData.h"
#include "UserSettings.h"

#include <string>
#include <sstream>
#include <iostream>

using namespace Supernova;

Scene scene;
Scene scene2;
Button button;
TextEdit textedit;
Lines lines;
Image imagem;
Texture textura;

void onPress();
void onTouchStart(int pointer, float x, float y);

void init(){
    Engine::setCanvasSize(1000, 480);
    Engine::setCallTouchInMouseEvent(true);

    button.setTexture("Button_Normal.png");
    button.setTexturePressed("Button_Disable.png");
    button.setPosition(100, 200, 0);
    button.setSize(400, 400);
    button.setBorder(16);
    //button.setLabelFont("arial.ttf");
    button.setLabelText("Eduardo");
    button.setLabelSize(80);
    button.setLabelColor(Vector4(0.2, 0.2, 0.2, 1.0));

    //textedit.setTextFont("arial.ttf");
    textedit.setTextColor(Vector4(0.4, 0.4, 0.4, 1.0));
    textedit.setPosition(300, 100, 0);
    textedit.setTexture("textedit.png");
    textedit.setBorder(8);
    textedit.setSize(200, 50);
    textedit.setText("");

    lines.setPosition(Vector3(300,300,0));
    lines.setColor(0.6, 0.2, 0.6, 1);
    lines.addLine(Vector3(0,0,0),Vector3(300,300,0));

    //scene2.addObject(&textedit);
    //scene2.setTextureFrame(&textura);

    //scene.addObject(&scene2);

    //imagem.setTexture(&textura);
    //imagem.setPosition(100,100);
    //imagem.setInvertTexture(true);
    //scene.addObject(&imagem);

    scene.addObject(&textedit);
    scene.addObject(&button);
    //scene.addObject(&lines);

    Engine::setScene(&scene);
    button.onUp = onPress;

    Engine::onTouchStart = onTouchStart;

}

void onTouchStart(int pointer, float x, float y){
    Log::Debug("TouchStart");
}

void onPress(){
    //text.setText("Eduardo Dória Lima");
    button.setPosition(150, 300);
}
#include "Supernova.h"
using namespace Supernova;


Scene scene;
Image window(&scene);
Button button(&scene);
Button button2(&scene);
TextEdit textedit(&scene);
Text text(&scene);

Container vcontainer(&scene);
Container hcontainer(&scene);

void onPress();
void onPress2();

void init(){
    Engine::setCanvasSize(1000, 480);
    Engine::setCallTouchInMouseEvent(true);
    Engine::setScalingMode(Scaling::NATIVE);

    vcontainer.addChild(&hcontainer);
    vcontainer.addChild(&button2);
    vcontainer.addChild(&text);
    vcontainer.setBoxExpand(2, true);
    vcontainer.setBoxExpand(1, false);
    vcontainer.setBoxExpand(0, true);

    hcontainer.addChild(&textedit);
    hcontainer.addChild(&button);
    hcontainer.setBoxExpand(true);

    //vcontainer.setSize(0,0);
    vcontainer.setType(ContainerType::VERTICAL);
    vcontainer.setName("vcontainer");
    vcontainer.setAnchorPreset(AnchorPreset::FULL_LAYOUT);
    //container.setBoxExpand(0, false);

    hcontainer.setType(ContainerType::HORIZONTAL);
    hcontainer.setName("hcontainer");
    hcontainer.setAnchorPreset(AnchorPreset::HORIZONTAL_CENTER_WIDE);

    button.setTexture("button_normal.png");
    button.setTexturePressed("button_disable.png");
    button.setPosition(100, 200, 0);
    button.setSize(200, 100);
    button.setPatchMargin(5);
    //button.setLabelFont("arial.ttf");
    button.setLabel("Insert");
    button.setName("button1");
    button.setFontSize(40);
    button.setLabelColor(Vector4(0.2, 0.2, 0.2, 1.0));
    button.getComponent<ButtonComponent>().onPress = onPress;
    button.setAnchorPreset(AnchorPreset::CENTER);

    button2.setTexture("button_normal.png");
    button2.setTexturePressed("button_disable.png");
    button2.setPosition(100, 200, 0);
    button2.setSize(200, 100);
    button2.setPatchMargin(5);
    button2.setLabel("Move position");
    button2.setName("button2");
    button2.setFontSize(40);
    button2.setLabelColor(Vector4(0.2, 0.2, 0.2, 1.0));
    button2.getComponent<ButtonComponent>().onPress = onPress2;
    button2.setAnchorPreset(AnchorPreset::HORIZONTAL_CENTER_WIDE);
    //button2.setAnchors(0.5, 0.5, 0.5, 0.5);
    //button2.setMargins(-200,-200, 200,200);

    textedit.setPosition(300, 50, 0);
    textedit.setTexture("textedit.png");
    textedit.setPatchMargin(5);
    textedit.setSize(200, 50);
    textedit.setText("");
    textedit.setName("textedit");
    textedit.setAnchorPreset(AnchorPreset::CENTER);
    //textedit.getComponent<UIComponent>().ignoreScissor = true;

    text.setText("Any text");
    text.setName("textobject");
    text.setColor(Vector4(0.2, 0.2, 0.2, 1.0));
    text.setAnchorPreset(AnchorPreset::CENTER_BOTTOM);

    window.setTexture("window.png");
    //window.getComponent<UIComponent>().texture.setMinFilter(TextureFilter::NEAREST_MIPMAP_NEAREST);
    //window.getComponent<UIComponent>().texture.setWrapU(TextureWrap::CLAMP_TO_EDGE);
    window.setPosition(0,0,0);
    window.setPatchMargin(10, 10, 50, 10);
    window.setSize(600,400);
    window.setName("window");
    window.setAnchorPreset(AnchorPreset::CENTER);

    window.addChild(&vcontainer);

    Engine::setScene(&scene);
}

void onPress(){
    text.setText(textedit.getText());
}

void onPress2(){
    if (text.getAnchorPreset() == AnchorPreset::CENTER_BOTTOM){
        text.setAnchorPreset(AnchorPreset::CENTER_RIGHT);
    }else if (text.getAnchorPreset() == AnchorPreset::CENTER_RIGHT){
        text.setAnchorPreset(AnchorPreset::CENTER_TOP);
    }else if (text.getAnchorPreset() == AnchorPreset::CENTER_TOP){
        text.setAnchorPreset(AnchorPreset::CENTER_LEFT);
    }else if (text.getAnchorPreset() == AnchorPreset::CENTER_LEFT){
        text.setAnchorPreset(AnchorPreset::CENTER_BOTTOM);
    }
}
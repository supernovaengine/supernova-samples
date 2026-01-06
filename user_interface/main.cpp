#include "Supernova.h"
using namespace Supernova;

Scene scene;

Panel window(&scene);
Container windowcontainer(&scene);
Container iconlist(&scene);
Scrollbar scroll(&scene);

Panel window2(&scene);
Button button(&scene);
Button button2(&scene);
TextEdit textedit(&scene);
Text text(&scene);
Container vcontainer(&scene);
Container hcontainer(&scene);

void onWindowResize(int width, int height);
void onChangeScroll(float step);
void onPress();
void onPress2();

SUPERNOVA_INIT void init(){
    Engine::setCanvasSize(1000, 480);
    Engine::setCallTouchInMouseEvent(true);
    Engine::setScalingMode(Scaling::NATIVE);

    window.setSize(430, 400);
    window.setTitle("Files");
    window.setTexture("window.png");
    window.setPatchMargin(10, 10, 50, 10);
    window.setPosition(50, 50);
    window.addChild(&windowcontainer);
    window.setName("window");
    window.getComponent<PanelComponent>().onResize = onWindowResize;

    windowcontainer.setType(ContainerType::HORIZONTAL);
    windowcontainer.setAnchorPreset(AnchorPreset::FULL_LAYOUT);
    windowcontainer.addChild(&iconlist);
    windowcontainer.addChild(&scroll);
    windowcontainer.setName("windowcontainer");
    windowcontainer.setBoxExpand(1, false);

    iconlist.setType(ContainerType::HORIZONTAL_WRAP);
    iconlist.setAnchorPreset(AnchorPreset::TOP_WIDE);
    iconlist.setName("iconlist");

    scroll.setSize(20, 20);
    scroll.setColor(0.5, 0.5, 0.5);
    scroll.setBarSize(0.6);
    scroll.setBarColor(0.8, 0.8, 0.8, 1.0);
    scroll.setStep(0.0);
    scroll.setType(ScrollbarType::VERTICAL);
    scroll.setAnchorPreset(AnchorPreset::VERTICAL_CENTER_WIDE);
    scroll.getComponent<ScrollbarComponent>().onChange = onChangeScroll;
    scroll.setBarTexture("button_normal.png");
    scroll.setBarPatchMargin(5);

    for (int i = 0; i < 22; i++){
        Container* iconset = new Container(window.getScene());
        Image* iconimage = new Image(window.getScene());
        Text* icontext = new Text(window.getScene());

        iconlist.addChild(iconset);

        iconset->addChild(iconimage);
        iconset->addChild(icontext);
        iconset->setName("iconset");
        iconset->setAnchorPreset(AnchorPreset::CENTER);

        iconimage->setTexture("paper_icon.png");
        iconimage->setSize(30, 40);
        iconimage->setAnchorPreset(AnchorPreset::CENTER);
        iconimage->setName("iconimage");
        icontext->setText("terrain_"+std::to_string(i)+".obj");
        icontext->setColor(0, 0, 0, 1);
        icontext->setFontSize(20);
        icontext->setAnchorPreset(AnchorPreset::CENTER);
    }

 // ==============================================

    vcontainer.addChild(&hcontainer);
    vcontainer.addChild(&button2);
    vcontainer.addChild(&text);
    vcontainer.setBoxExpand(0, true);
    vcontainer.setBoxExpand(1, false);
    vcontainer.setBoxExpand(2, true);

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
    button.setLabelFontSize(40);
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
    button2.setLabelFontSize(40);
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

    window2.setTexture("window.png");
    //window.getComponent<UIComponent>().texture.setMinFilter(TextureFilter::NEAREST_MIPMAP_NEAREST);
    //window.getComponent<UIComponent>().texture.setWrapU(TextureWrap::CLAMP_TO_EDGE);
    window2.setPosition(300,20,0);
    window2.setPatchMargin(10, 10, 50, 10);
    window2.setSize(600,400);
    window2.setName("window");
    window2.setTitle("Window");
    //window.setAnchorPreset(AnchorPreset::CENTER);
    window2.addChild(&vcontainer);

    Engine::setScene(&scene);
}

void onWindowResize(int width, int height){
    float bar = (float)windowcontainer.getHeight() / (float)iconlist.getHeight();

    scroll.setBarSize(bar);

    if (bar >= 1){
        scroll.setVisible(false);
    }else{
        scroll.setVisible(true);
    }
}

void onChangeScroll(float step){
    int diff = iconlist.getHeight() - windowcontainer.getHeight();

    iconlist.setPositionOffset(Vector2(0, -step*diff));
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
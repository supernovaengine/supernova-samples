#include "Supernova.h"
using namespace Supernova;

void onKeyDown(int key, bool repeat, int mods);
void onTouchStart(int pointer, float x, float y);
void onTouchMove(int pointer, float x, float y);

Vector2 lastTouchPos;

Scene scene;

Camera camera(&scene);
Shape terrain(&scene);
Model model(&scene);
SkyBox sky(&scene);
Light* sun = NULL;

Scene uiscene;
Text text(&uiscene);


void init(){
    scene.setGlobalIllumination(0.1);
    scene.setCamera(camera.getEntity());

    text.setText("Press any key to start");
    text.setAnchorPreset(AnchorPreset::CENTER_TOP);

    camera.setPosition(0, 7, -20);
    camera.setTarget(0, 2, 0);

    terrain.createPlane(200, 200);
    terrain.setTexture("ground.png");

    model.loadModel("CesiumMan.glb");
    model.setScale(4);
    model.setRotation(-90,0,0);
    model.getAnimation(0).setLoop(true);

    if (!sun)
        sun = new Light(&scene);
    sun->setType(LightType::DIRECTIONAL);
    sun->setDirection(0,-0.7, 0.8);
    sun->setIntensity(10);
    sun->setShadows(true);

    sky.setTextureFront("ely_hills/hills_lf.tga");
    sky.setTextureBack("ely_hills/hills_rt.tga");
    sky.setTextureLeft("ely_hills/hills_bk.tga");
    sky.setTextureRight("ely_hills/hills_ft.tga");
    sky.setTextureUp("ely_hills/hills_up.tga");
    sky.setTextureDown("ely_hills/hills_dn.tga");

    Engine::setScalingMode(Scaling::FITWIDTH);
    Engine::setCanvasSize(1000, 480);
    Engine::setScene(&scene);
    Engine::addSceneLayer(&uiscene);
    Engine::setCallTouchInMouseEvent(true);

    Engine::onKeyDown = onKeyDown;
    Engine::onTouchStart = onTouchStart;
    Engine::onTouchMove = onTouchMove;
}

void onKeyDown(int key, bool repeat, int mods){
    model.getAnimation(0).start();
}

void onTouchMove(int pointer, float x, float y){
    float difX = lastTouchPos.x - x;
    float difY = lastTouchPos.y - y;
    lastTouchPos = Vector2(x, y);

    camera.rotatePosition(0.1 * difX);
    camera.elevatePosition(-0.1 * difY);
}

void onTouchStart(int pointer, float x, float y){
    lastTouchPos = Vector2(x, y);
}

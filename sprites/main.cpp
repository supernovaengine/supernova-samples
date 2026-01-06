#include "Supernova.h"
using namespace Supernova;

Scene scene;

Camera camera(&scene);

Sprite sprite(&scene);
Sprite sprite2(&scene);
SpriteAnimation spriteanim(&scene);

void onActionStart();
void onTouchStart(int pointer, float x, float y);

SUPERNOVA_INIT void init(){

    camera.setType(CameraType::CAMERA_ORTHO);
    scene.setCamera(camera.getEntity());

    sprite.setTexture("dino.png");
    for (int i = 0; i < 8; i++)
        sprite.addFrame(i, "", Rect((i+1.0)/8, 0.0, 1.0/8, 1.0));
    sprite.setFrame(0);
    sprite.setName("Sprite");
    sprite.setPosition(100,200,0);
    sprite.setSize(200,200);

    spriteanim.setTarget(sprite.getEntity());
    spriteanim.setAnimation(0, 7, 100, true);
    spriteanim.getComponent<ActionComponent>().onStart = onActionStart;


    sprite2.setTexture("dino.png");
    for (int i = 0; i < 8; i++)
        sprite2.addFrame(i, "", Rect((i+1.0)/8, 0.0, 1.0/8, 1.0));
    sprite2.setFrame(0);
    sprite.setName("Sprite");
    sprite2.setPosition(400,200,0);
    sprite2.setSize(200,200);

    Engine::setScene(&scene);
    Engine::setCallTouchInMouseEvent(true);

    Engine::onTouchStart = onTouchStart;
}

void onTouchStart(int pointer, float x, float y) {
    spriteanim.start();
    sprite2.startAnimation(0, 7, 200, true);
}

void onActionStart(){
    Log::verbose("Sprite start");
}
#include "Supernova.h"
using namespace Supernova;

#include "Sprite.h"
#include "SpriteAnimation.h"
#include "MeshPolygon.h"
#include "Input.h"
#include "Angle.h"

Scene scene;

Sprite sprite(&scene);
Sprite sprite2(&scene);
SpriteAnimation spriteanim(&scene);

void onActionStart();
void onTouchStart(int pointer, float x, float y);

void init(){

    sprite.setTexture("dino.png");
    for (int i = 0; i < 8; i++)
        sprite.addFrame(i, "", Rect((i+1.0)/8, 0.0, 1.0/8, 1.0));
    sprite.setFrame(0);
    sprite.setName("Sprite");
    sprite.setPosition(20,20,0);
    sprite.setSize(200,200);

    spriteanim.setTarget(sprite.getEntity());
    spriteanim.setAnimation(0, 7, 100, true);
    spriteanim.getComponent<ActionComponent>().onStart = onActionStart;


    sprite2.setTexture("dino.png");
    for (int i = 0; i < 8; i++)
        sprite2.addFrame(i, "", Rect((i+1.0)/8, 0.0, 1.0/8, 1.0));
    sprite2.setFrame(0);
    sprite.setName("Sprite");
    sprite2.setPosition(400,20,0);
    sprite2.setSize(200,200);

    //Engine::setScene(&scene);
    //Engine::setCallTouchInMouseEvent(true);

    //Engine::onTouchStart = onTouchStart;
}

void onTouchStart(int pointer, float x, float y) {
    spriteanim.start();
    sprite2.startAnimation(0, 7, 200, true);
}

void onActionStart(){
    Log::verbose("Sprite start");
}
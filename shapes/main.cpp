#include "Supernova.h"

#include "Scene.h"
#include "Camera.h"
#include "TimedAction.h"
#include "Angle.h"
#include "Shape.h"

using namespace Supernova;

void onActionStep();
void onKeyDown(int key, bool repeat, int mods);
void onTouchStart(int pointer, float x, float y);
void onTouchMove(int pointer, float x, float y);

Vector2 lastTouchPos;

Scene scene;

Camera camera(&scene);
Shape torus(&scene);
Shape cylinder(&scene);
Shape cube(&scene);
Shape sphere(&scene);
Shape plane(&scene);

TimedAction timedaction(&scene);


void init(){
    scene.setCamera(camera.getEntity());

    camera.setPosition(0, 30, 30);
    camera.setName("camera");

    torus.createTorus(3, 1);
    torus.setTexture("block.png");
    torus.setPosition(0,0,-10);

    cylinder.createCylinder(1, 3);
    cylinder.setTexture("block.png");
    cylinder.setPosition(-10,0,0);

    cube.createBox(4, 4, 4);
    cube.setTexture("block.png");
    cube.setPosition(0,0,0);

    sphere.createSphere(3);
    sphere.setTexture("block.png");
    sphere.setPosition(0,0,10);

    plane.createPlane(5, 5);
    plane.setTexture("block.png");
    plane.setPosition(10,0,0);

    timedaction.setDuration(5);
    timedaction.setLoop(true);
    timedaction.getComponent<ActionComponent>().onStep = onActionStep;
    timedaction.start();
    
    Engine::setScene(&scene);
    Engine::setCallTouchInMouseEvent(true);

    Engine::onTouchStart = onTouchStart;
    Engine::onTouchMove = onTouchMove;
}

void onActionStep(){
    float angle = timedaction.getValue() * 360;

    Quaternion rot;
    rot.fromAngle(Angle::degToDefault(angle));

    torus.setRotation(rot);
    cylinder.setRotation(rot);
    cube.setRotation(rot);
    sphere.setRotation(rot);
    plane.setRotation(rot);
}

void onTouchMove(int pointer, float x, float y){
    float difX = lastTouchPos.x - x;
    float difY = lastTouchPos.y - y;
    lastTouchPos = Vector2(x, y);

    camera.rotateView(0.1 * difX);
    camera.elevateView(0.1 * difY);
}

void onTouchStart(int pointer, float x, float y){
    lastTouchPos = Vector2(x, y);
}

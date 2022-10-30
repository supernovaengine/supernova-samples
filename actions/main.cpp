#include "Supernova.h"
using namespace Supernova;

#include "Polygon.h"
#include "MeshPolygon.h"
#include "Input.h"
#include "Angle.h"
#include "PositionAction.h"
#include "RotationAction.h"
#include "ScaleAction.h"
#include "ColorAction.h"
#include "AlphaAction.h"

Scene scene;

MeshPolygon polygon(&scene);
MeshPolygon polygon2(&scene);
Polygon polygon3(&scene);
PositionAction positionaction(&scene);
RotationAction rotationaction(&scene);
ScaleAction scaleaction(&scene);
ColorAction coloraction(&scene);
AlphaAction alphaaction(&scene);


void onActionStart();
void onTouchStart(int pointer, float x, float y);

void init(){

    polygon.addVertex(0, 0);
    polygon.addVertex(200, 0);
    polygon.addVertex(0, 200);
    polygon.addVertex(200, 200);
    polygon.setColor(1.0, 0.3, 0.8, 1.0);
    polygon.setPosition(50, 50, 0);
    polygon.setName("Polygon1");

    polygon2.addVertex(0, 0);
    polygon2.addVertex(200, 0);
    polygon2.addVertex(0, 200);
    polygon2.addVertex(200, 200);
    polygon2.setColor(1.0, 0.5, 1.0, 1.0);
    polygon2.setPosition(350, 50, 0);
    polygon2.setName("Polygon2");

    polygon3.addVertex(0, 0);
    polygon3.addVertex(200, 0);
    polygon3.addVertex(0, 200);
    polygon3.addVertex(200, 200);
    polygon3.setColor(0.5, 1.0, 1.0, 1.0);
    polygon3.setPosition(650, 50, 0);
    polygon3.setName("Polygon3");

    Quaternion startRot;
    Quaternion endRot;
    startRot.fromAngle(Angle::degToDefault(0));
    endRot.fromAngle(Angle::degToDefault(180));
    rotationaction.setAction(startRot, endRot, 5, false);
    rotationaction.setTarget(polygon3.getEntity());
    rotationaction.getComponent<ActionComponent>().onStart = onActionStart;

    scaleaction.setAction(Vector3(1,1,1), Vector3(2,2,2), 10, false);
    scaleaction.setTarget(polygon2.getEntity());

    coloraction.setAction(polygon.getColor(), Vector4(0.0, 0.0, 1.0, 1.0), 5, false);
    coloraction.setTarget(polygon.getEntity());

    alphaaction.setAction(1.0, 0.3, 5, false);
    alphaaction.setTarget(polygon2.getEntity());

    positionaction.setAction(Vector3(20,20,0), Vector3(200,200,0), 5, true);
    positionaction.setTarget(polygon.getEntity());
    positionaction.setFunctionType(EaseType::ELASTIC_IN_OUT);
    positionaction.setSpeed(1);

    Engine::setScene(&scene);
    Engine::setCallTouchInMouseEvent(true);

    Engine::onTouchStart = onTouchStart;
}

void onTouchStart(int pointer, float x, float y) {
    positionaction.start();
    rotationaction.start();
    scaleaction.start();
    coloraction.start();
    alphaaction.start();
}

void onActionStart(){
    Log::verbose("Action Start");
}
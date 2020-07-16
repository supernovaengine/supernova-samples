#include "Supernova.h"

#include "Scene.h"
#include "Polygon.h"
#include "Points.h"
#include "MoveAction.h"
#include "Log.h"
#include "File.h"

using namespace Supernova;
Polygon* triangulo;
Scene cena;
MoveAction* move;

void onKeyDown(int key){
    //delete triangulo;
    //move->run();
}

void onTouchStart(int pointer, float width, float height){
    //delete triangulo;
    move->run();
}

void init(){
    Engine::setCanvasSize(1000,480);
    Engine::setCallTouchInMouseEvent(true);

    triangulo = new Polygon();

    triangulo->addVertex(Vector3(0, -100, 0));
    triangulo->addVertex(Vector3(-50, 50, 0));
    triangulo->addVertex(Vector3(50, 50, 0));

    triangulo->setPosition(Vector3(300,300,0));
    triangulo->setColor(0.6, 0.2, 0.6, 1);

    move = new MoveAction(Vector3(300,300,0), Vector3(600,600,0), 5);
    move->setFunctionType(S_EASE_ELASTIC_IN_OUT);
    triangulo->addAction(move);

    //som.play();

    cena.addObject(triangulo);

    Engine::onKeyDown = onKeyDown;
    Engine::onTouchStart = onTouchStart;
    Engine::setScene(&cena);
}
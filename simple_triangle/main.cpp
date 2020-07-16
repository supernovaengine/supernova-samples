#include "Supernova.h"

#include "Scene.h"
#include "Polygon.h"

using namespace Supernova;
Polygon triangulo;
Scene cena;

void init(){
    Engine::setCanvasSize(1000,480);

    triangulo.addVertex(Vector3(0, -100, 0));
    triangulo.addVertex(Vector3(-50, 50, 0));
    triangulo.addVertex(Vector3(50, 50, 0));

    triangulo.setPosition(Vector3(300,300,0));
    triangulo.setColor(0.6, 0.2, 0.6, 1);
    cena.addObject(&triangulo);

    Engine::setScene(&cena);
}
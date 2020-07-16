#include "Supernova.h"
#include "Scene.h"
#include "PhysicsWorld2D.h"
#include "Body2D.h"
#include "CollisionShape2D.h"
#include "Log.h"

#include "Image.h"

using namespace Supernova;

Scene scene;
Image imagem1;
Image imagem2;
PhysicsWorld2D *world;
Body2D *body1;
Body2D *body2;

void onTouchStart(int pointer, float x, float y){
    //world->addBody(body1);
    //world->addBody(body2);
    body1->setPosition(Vector2(300, 0));
}


void init(){
    Engine::setCanvasSize(1280, 720);

    Engine::setCallTouchInMouseEvent(true);

    //scene.setPosition(200,200);

    imagem1.setTexture("block.png");
    imagem1.setPosition(200,0);
    imagem1.setSize(100,100);
    imagem1.setCenter(Vector2(50, 50));

    imagem2.setTexture("ground.png");
    imagem2.setPosition(100, 500);
    imagem2.setSize(500,100);

    scene.createPhysicsWorld2D();
    scene.getPhysicsWorld()->setGravity(0, 5);
    scene.getPhysicsWorld()->setWorldSpace(true);

    body1 = imagem1.createBody2D();
    CollisionShape2D* shape1 = new CollisionShape2D();
    //shape1->setShapeBox(100,100);
    //shape1->setCenter(50,50);
    shape1->setShapeCircle(Vector2(0,0), 50);
    shape1->setPosition(50,50);
    shape1->setDensity(1.0);
    body1->addCollisionShape(shape1);
    body1->setLinearVelocity(Vector2(1,0));

    //body1->createBox(100,100,Vector2(50,50));
    //body1->setDensity(1.0);
    body1->setType(S_BODY2D_DYNAMIC);

    body2 = imagem2.createBody2D();
    body2->createBox(500,100);

    scene.addObject(&imagem1);
    scene.addObject(&imagem2);

    Engine::setScene(&scene);

    Engine::onTouchStart = onTouchStart;
}
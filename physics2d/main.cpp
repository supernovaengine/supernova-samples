#include "Supernova.h"
using namespace Supernova;

#define MAXCRATES 4

Scene scene;
Camera camera(&scene);
Image* crates[MAXCRATES];
Image* ball;
Joint2D joint(&scene);

Scene uiscene;
Text text(&uiscene);


void startPositions();
void onKeyDown(int key, bool repeat, int mods);


bool shouldCollide(Body2D bA, size_t sA, Body2D bB, size_t sB){
    printf("Should collide %s %s\n", bA.getAttachedObject().getName().c_str(), bB.getAttachedObject().getName().c_str());
    return true;
}

void beginContact2D(Contact2D contact){
    printf("beginContact2D %s %s\n", contact.getBodyA().getAttachedObject().getName().c_str(), contact.getBodyB().getAttachedObject().getName().c_str());
}

void endContact2D(Contact2D contact){
    printf("endContact2D %s %s\n", contact.getBodyA().getAttachedObject().getName().c_str(), contact.getBodyB().getAttachedObject().getName().c_str());
}

void preSolve2D(Contact2D contact, Manifold2D manifold){
    printf("preSolve2D %s %s\n", contact.getBodyA().getAttachedObject().getName().c_str(), contact.getBodyB().getAttachedObject().getName().c_str());
}

void postSolve2D(Contact2D contact, ContactImpulse2D contactImpulse){
    printf("postSolve2D %s %s\n", contact.getBodyA().getAttachedObject().getName().c_str(), contact.getBodyB().getAttachedObject().getName().c_str());
}


void init(){

    text.setText("Press any key to reset");
    text.setAnchorPreset(AnchorPreset::CENTER_TOP);

    for (int i = 0; i < MAXCRATES; i++){
        crates[i] = new Image(&scene);
    }
    ball = new Image(&scene);

    startPositions();

    camera.setType(CameraType::CAMERA_ORTHO);
    scene.setCamera(camera.getEntity());
    scene.setBackgroundColor(0.6, 0.6, 0.6);


    crates[0]->setTexture("crate.png");
    crates[0]->setName("crate0");
    crates[0]->setSize(100, 100);

    Body2D body =  crates[0]->getBody2D();
    body.createRectShape(100, 100);
    body.setShapeDensity(1.0);
    body.setType(BodyType::DYNAMIC);


    crates[1]->setTexture("crate.png");
    crates[1]->setName("crate1");
    crates[1]->setSize(100, 100);

    Body2D body1 = crates[1]->getBody2D();
    body1.createRectShape(100, 100);
    body1.setShapeDensity(1.0);
    //body1.setType(Body2DType::DYNAMIC);


    crates[2]->setTexture("crate.png");
    crates[2]->setName("crate2");
    crates[2]->setSize(100, 100);

    Body2D body2 = crates[2]->getBody2D();
    body2.createRectShape(100, 100);
    body2.setShapeDensity(1.0);
    body2.setType(BodyType::DYNAMIC);


    crates[3]->setTexture("crate.png");
    crates[3]->setName("crate3");
    crates[3]->setSize(100, 100);

    Body2D body3 = crates[3]->getBody2D();
    body3.createRectShape(100, 100);
    body3.setShapeDensity(1.0);
    //body3.setType(BodyType::DYNAMIC);


    ball->setTexture("SoccerBall.png");
    ball->setName("soccerball");
    ball->setSize(50, 50);

    Body2D bodyball = ball->getBody2D();
    bodyball.createCircleShape(Vector2(25, 25), 25);
    bodyball.setShapeDensity(1.0);
    bodyball.setType(BodyType::DYNAMIC);


    scene.getSystem<PhysicsSystem>()->shouldCollide2D = shouldCollide;
    scene.getSystem<PhysicsSystem>()->beginContact2D = beginContact2D;
    scene.getSystem<PhysicsSystem>()->endContact2D = endContact2D;
    scene.getSystem<PhysicsSystem>()->preSolve2D = preSolve2D;
    scene.getSystem<PhysicsSystem>()->postSolve2D = postSolve2D;

    //scene.getSystem<PhysicsSystem>()->setGravity(0,10);

    joint.setDistanceJoint(body2.getEntity(), body3.getEntity(), Vector2(500, 300), Vector2(700, 300));

    Engine::setScalingMode(Scaling::FITWIDTH);
    Engine::setCanvasSize(1000,480);
    Engine::setScene(&scene);
    Engine::addSceneLayer(&uiscene);

    Engine::onKeyDown = onKeyDown;
}

void startPositions(){
    crates[0]->setPosition(140, 600);
    //crates[0]->setRotation(0, 0, 0);
    crates[0]->getBody2D().setLinearVelocity(Vector2(0, 0));
    crates[0]->getBody2D().setAngularVelocity(0);
    crates[0]->getBody2D().setLinearDamping(0);
    crates[0]->getBody2D().setAngularDamping(0);
    crates[0]->getBody2D().resetMassData();

    crates[1]->setPosition(80, 100);
    crates[1]->getBody2D().setLinearVelocity(Vector2(0, 0));

    crates[2]->setPosition(500, 300);
    crates[2]->getBody2D().setLinearVelocity(Vector2(0, 0));

    crates[3]->setPosition(700, 300);
    crates[3]->getBody2D().setLinearVelocity(Vector2(0, 0));

    ball->setPosition(100, 450);
    ball->getBody2D().setLinearVelocity(Vector2(0, 0)); 
}

void onKeyDown(int key, bool repeat, int mods){
    startPositions();
}

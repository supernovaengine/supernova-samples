#include "Supernova.h"
using namespace Supernova;

#define MAXCRATES 4

Scene scene;
Camera camera(&scene);
Sprite* crates[MAXCRATES];
Sprite* ball;
Joint2D joint(&scene);

Lines lines(&scene);
Points points(&scene);

Scene uiscene;
Text text(&uiscene);

void onUpdate();
void onKeyDown(int key, bool repeat, int mods);


bool shouldCollide(Body2D bA, size_t sA, Body2D bB, size_t sB){
    printf("Should collide %s %lu %s %lu\n", bA.getAttachedObject().getName().c_str(), sA, bB.getAttachedObject().getName().c_str(), sB);
    return true;
}

void beginContact2D(Body2D bA, size_t sA, Body2D bB, size_t sB){
    printf("beginContact2D %s %lu %s %lu\n", bA.getAttachedObject().getName().c_str(), sA, bB.getAttachedObject().getName().c_str(), sB);
}

void endContact2D(Body2D bA, size_t sA, Body2D bB, size_t sB){
    printf("endContact2D %s %lu %s %lu\n", bA.getAttachedObject().getName().c_str(), sA, bB.getAttachedObject().getName().c_str(), sB);
}

void hitContact2D(Body2D bA, size_t sA, Body2D bB, size_t sB, Vector2 point, Vector2 normal, float approachSpeed){
    printf("hitContact2D %s %lu %s %lu (%f %f) (%f %f) %f\n", 
        bA.getAttachedObject().getName().c_str(), sA, 
        bB.getAttachedObject().getName().c_str(), sB,
        point.x, point.y, normal.x, normal.y, approachSpeed);
}

bool preSolve2D(Body2D bA, size_t sA, Body2D bB, size_t sB, Manifold2D manifold){
    printf("preSolve2D %s %lu %s %lu\n", bA.getAttachedObject().getName().c_str(), sA, bB.getAttachedObject().getName().c_str(), sB);
    return true;
}

void startPositions(){
    crates[0]->setPosition(170, 600);
    //crates[0]->setRotation(0, 0, 0);
    crates[0]->getBody2D().setLinearVelocity(Vector2(0, 0));
    crates[0]->getBody2D().setAngularVelocity(0);
    crates[0]->getBody2D().setLinearDamping(0);
    crates[0]->getBody2D().setAngularDamping(0);
    crates[0]->getBody2D().applyMassFromShapes();

    crates[1]->setPosition(110, 100);
    crates[1]->getBody2D().setLinearVelocity(Vector2(0, 0));

    crates[2]->setPosition(500, 300);
    crates[2]->getBody2D().setLinearVelocity(Vector2(0, 0));

    crates[3]->setPosition(700, 300);
    crates[3]->getBody2D().setLinearVelocity(Vector2(0, 0));

    ball->setPosition(130, 450);
    ball->getBody2D().setLinearVelocity(Vector2(0, 0)); 
}


void init(){

    text.setText("Press any key to reset");
    text.setAnchorPreset(AnchorPreset::CENTER_TOP);

    for (int i = 0; i < MAXCRATES; i++){
        crates[i] = new Sprite(&scene);
    }
    ball = new Sprite(&scene);

    camera.setType(CameraType::CAMERA_ORTHO);
    scene.setCamera(camera.getEntity());
    scene.setBackgroundColor(0.6, 0.6, 0.6);


    crates[0]->setTexture("crate.png");
    crates[0]->setName("crate0");
    crates[0]->setSize(100, 100);
    crates[0]->setPivotPreset(PivotPreset::CENTER);

    Body2D body =  crates[0]->getBody2D();
    body.createCenteredBoxShape(100, 100, Vector2(0,0), 0);
    body.setShapeDensity(1.0);
    body.load();


    crates[1]->setTexture("crate.png");
    crates[1]->setName("crate1");
    crates[1]->setSize(100, 100);
    crates[1]->setPivotPreset(PivotPreset::CENTER);

    Body2D body1 = crates[1]->getBody2D();
    body1.createCenteredBoxShape(100, 100);
    body1.setShapeDensity(1.0);
    body1.setShapeEnableHitEvents(true);
    body1.setShapePreSolveEvents(true);
    body1.setType(BodyType::STATIC);
    body1.load();


    crates[2]->setTexture("crate.png");
    crates[2]->setName("crate2");
    crates[2]->setSize(100, 100);
    crates[2]->setPivotPreset(PivotPreset::CENTER);

    Body2D body2 = crates[2]->getBody2D();
    body2.createCenteredBoxShape(100, 100);
    body2.setShapeDensity(1.0);
    body2.load();


    crates[3]->setTexture("crate.png");
    crates[3]->setName("crate3");
    crates[3]->setSize(100, 100);
    crates[3]->setPivotPreset(PivotPreset::CENTER);

    Body2D body3 = crates[3]->getBody2D();
    body3.createCenteredBoxShape(100, 100);
    body3.setShapeDensity(1.0);
    body3.setType(BodyType::STATIC);
    body3.load();


    ball->setTexture("SoccerBall.png");
    ball->setName("soccerball");
    ball->setSize(50, 50);
    ball->setPivotPreset(PivotPreset::CENTER);

    Body2D bodyball = ball->getBody2D();
    bodyball.createCircleShape(Vector2(0, 0), 25);
    bodyball.setShapeDensity(1.0);
    bodyball.load();

    startPositions();

    scene.getSystem<PhysicsSystem>()->shouldCollide2D = shouldCollide;
    scene.getSystem<PhysicsSystem>()->beginContact2D = beginContact2D;
    scene.getSystem<PhysicsSystem>()->endContact2D = endContact2D;
    scene.getSystem<PhysicsSystem>()->hitContact2D = hitContact2D;
    scene.getSystem<PhysicsSystem>()->preSolve2D = preSolve2D;

    //scene.getSystem<PhysicsSystem>()->setGravity(0,10);

    joint.setDistanceJoint(body2.getEntity(), body3.getEntity(), Vector2(crates[2]->getPosition()), Vector2(crates[3]->getPosition()), false);

    lines.addLine(Vector3(725, 0, 0), Vector3(725, 500, 0));
    points.addPoint(Vector3(0, 0, 0), Vector4(1, 0, 1, 1), 10);
    points.setPointVisible(0, false);

    Engine::setScalingMode(Scaling::FITWIDTH);
    Engine::setCanvasSize(1000,480);
    Engine::setScene(&scene);
    Engine::addSceneLayer(&uiscene);

    Engine::onUpdate = onUpdate;
    Engine::onKeyDown = onKeyDown;
}

void onUpdate(){
    Ray ray(Vector3(725, 0, 0), Vector3(0, 500, 0));
    RayReturn rret = ray.intersects(&scene, RayFilter::BODY_2D);

    if (rret.hit){
        points.updatePoint(0, rret.point);
        points.setPointVisible(0, true);
    }else{
        points.setPointVisible(0, false);
    }
}

void onKeyDown(int key, bool repeat, int mods){
    startPositions();
}

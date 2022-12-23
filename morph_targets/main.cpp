#include "Supernova.h"

#include "Scene.h"
#include "Camera.h"
#include "Model.h"
#include "SkyBox.h"
#include "Light.h"

using namespace Supernova;

void onKeyDown(int key, bool repeat, int mods);
void onTouchStart(int pointer, float x, float y);

Scene scene;

Camera camera(&scene);
Mesh terrain(&scene);
Model model(&scene);
SkyBox sky(&scene);


void init(){
    scene.setAmbientLight(0.2);
    scene.setCamera(camera.getEntity());

    camera.setPosition(0, 7, -20);

    terrain.createPlane(200, 200);
    terrain.setTexture("ground.png");
    terrain.setPosition(-100,0,-100);

    model.loadModel("AnimatedMorphCube.gltf");
    model.setScale(100);
    model.setPosition(0,1,0);
    model.setRotation(0,90,0);
    model.getAnimation(0).setLoop(true);

    Light* sun = new Light(&scene);
    sun->setType(LightType::DIRECTIONAL);
    sun->setDirection(0,-0.7, 0.8);
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
    Engine::setCallTouchInMouseEvent(true);

    Engine::onKeyDown = onKeyDown;
    Engine::onTouchStart = onTouchStart;
}

void onKeyDown(int key, bool repeat, int mods){
    model.getAnimation(0).start();
}

void onTouchStart(int pointer, float x, float y){
    model.getAnimation(0).start();
}

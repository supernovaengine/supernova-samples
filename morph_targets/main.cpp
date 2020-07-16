#include "Supernova.h"

#include "Scene.h"
#include "Camera.h"
#include "PlaneTerrain.h"
#include "Log.h"
#include "Model.h"
#include "math/Angle.h"
#include <math.h>
#include "DirectionalLight.h"
#include "Text.h"

using namespace Supernova;

void onUpdate();
void onKeyDown(int key);
void onTouchStart(int pointer, float x, float y);

Camera camera;
Scene cena;
PlaneTerrain plano(2000, 2000);
Model carro("AnimatedMorphCube.gltf");
SkyBox sky;

float rotacao = 0;

void init(){
    Engine::setScalingMode(Scaling::FITWIDTH);
    Engine::setCanvasSize(1000, 480);

    cena.setAmbientLight(0.5);

    camera.setPosition(0, 50, -100);

    plano.setTexture("ground.png");
    plano.setPosition(-1000,0,-1000);

    carro.setScale(400);
    carro.setRotation(-90,0,0);
    carro.setPosition(0, 30, 0);

    DirectionalLight* sol = new DirectionalLight();
    sol->setDirection(0,-0.7,-0.8);
    sol->setShadow(false);
    cena.addObject(sol);

    sky.setTextureFront("ely_hills/hills_lf.tga");
    sky.setTextureBack("ely_hills/hills_rt.tga");
    sky.setTextureLeft("ely_hills/hills_bk.tga");
    sky.setTextureRight("ely_hills/hills_ft.tga");
    sky.setTextureUp("ely_hills/hills_up.tga");
    sky.setTextureDown("ely_hills/hills_dn.tga");

    cena.addObject(&plano);
    cena.addObject(&carro);
    cena.addObject(&sky);
    cena.setCamera(&camera);

    Engine::setScene(&cena);

    Engine::onUpdate = onUpdate;
    Engine::onKeyDown = onKeyDown;
    Engine::onTouchStart = onTouchStart;
}

void onUpdate(){
    rotacao = rotacao + 1;
    if (rotacao > 360) rotacao = rotacao - 360;
    if (rotacao < 0) rotacao = 360 + rotacao;

    carro.setRotation(-90, rotacao, 0);

    camera.setView(carro.getPosition());
}

void onKeyDown(int key){
    carro.getAnimation(0)->run();
}

void onTouchStart(int pointer, float x, float y){
    carro.getAnimation(0)->run();
}
#include "Supernova.h"

#include "Scene.h"
#include "Polygon.h"
#include "Cube.h"
#include "Camera.h"
#include "PlaneTerrain.h"
#include "Model.h"
#include "math/Angle.h"
#include <math.h>
#include "SpotLight.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Particles.h"
#include "Image.h"
#include "Text.h"
#include "Input.h"

using namespace Supernova;

void onUpdate();
void onKeyDown(int key);
void onKeyUp(int key);
void onTouchStart(int pointer, float x, float y);
void onTouchDrag(int pointer, float x, float y);
void onTouchEnd(int pointer, float x, float y);

Camera camera;
Scene cena;
Scene cena2;
PlaneTerrain plano(2000,2000);
Model carro("jeep/Jeep.obj");
Model casa("old-house/old-house.obj");
SkyBox sky;
Text texto;
//Cube cubo (20,20,20);
Vector2 analogCenter;
Fog fog;


float curva = 0;
float velocidade = 0;
float rotacao = 0;

bool up, down, left, right;

void init(){
    printf("entrou em cpp\n");

    //Engine::setScalingMode(S_SCALING_LETTERBOX);
    Engine::setCanvasSize(1000, 480);

    cena.setAmbientLight(0.5);

    camera.setPosition(0, 50, 200);
    //camera.setPosition(0, 10, -25);
    //camera.setView(0,10,0);
    //camera.attachToObject(&carro);

    //carro.loadTextureFile("block.png");
    //carro.setCenter(0,0,5);

    casa.setScale(10);
    casa.setRotation(-90,180,0);
    casa.setPosition(60,0,60);

    plano.setTexture("road.png");
    plano.setPosition(-1000,0,-1000);

    carro.setScale(5);
    //carro.setTexture("Jeep_outside_d.png");
    carro.setCenter(0,0,-5);

    fog.setLinearStart(10);
    fog.setLinearEnd(100);
    //cena.setFog(&fog);

    SpotLight* farol = new SpotLight();
    farol->setSpotAngle(80);
    farol->setPosition(0,5,8);
    farol->setTarget(0,0,30);
    farol->setPower(100);
    farol->setShadowBias(0.00003);
    farol->setShadow(true);
    carro.addObject(farol);

    PointLight* luz = new PointLight();
    luz->setPosition(20,40,8);
    luz->setPower(100);
    luz->setShadow(true);
    cena.addObject(luz);

    DirectionalLight* sol = new DirectionalLight();
    sol->setDirection(0,-0.7,0.3);
    sol->setShadow(true);
    //cena.addObject(sol);

    sky.setTextureFront("ely_hills/hills_lf.tga");
    sky.setTextureBack("ely_hills/hills_rt.tga");
    sky.setTextureLeft("ely_hills/hills_bk.tga");
    sky.setTextureRight("ely_hills/hills_ft.tga");
    sky.setTextureUp("ely_hills/hills_up.tga");
    sky.setTextureDown("ely_hills/hills_dn.tga");

    //cubo.setTexture("block.png");
    //cubo.setPosition(30,0,30);
    //cena.addObject(&cubo);

    cena.addObject(&plano);
    cena.addObject(&carro);
    cena.addObject(&casa);
    cena.addObject(&sky);

    texto.setText("");
    texto.setPosition(100, 100, 0);
    //texto.setWidth(200);
    cena2.addObject(&texto);

    cena.addObject(&cena2);
    cena.setCamera(&camera);

    Engine::setUpdateTime(20);

    Engine::setScene(&cena);

    Engine::onUpdate = onUpdate;
    Engine::onKeyDown = onKeyDown;
    Engine::onTouchStart = onTouchStart;
    Engine::onTouchDrag = onTouchDrag;
    Engine::onTouchEnd = onTouchEnd;
    Engine::onKeyUp = onKeyUp;
}

void onUpdate(){

    texto.setText(std::to_string(Engine::getFramerate()).c_str());

    if (up){
        velocidade += 0.3;
    }else if (down){
        velocidade -= 0.3;
    }
    velocidade *= 0.98;

    if (left){
        if (curva < 3)
            curva += 0.4;
    }else if (right){
        if (curva > -3)
            curva -= 0.4;
    }else{
        curva = 0;
    }

    if (Input::isKeyPressed(S_KEY_B)){
        printf("testando B\n");
    }
    if (Input::isKeyPressed(S_KEY_A)){
        printf("testando A\n");
        printf("MousePosition %f %f\n", Input::getMousePosition().x, Input::getMousePosition().y);
    }

    rotacao = rotacao + curva;
    if (rotacao > 360)    rotacao = rotacao - 360;
    if (rotacao < 0)    rotacao = 360 + rotacao;

    Vector3 vDirecao(cos(Angle::degToRad(rotacao-90)), 0, -sin(Angle::degToRad(rotacao-90)));

    carro.setRotation(0,rotacao,0);
    carro.setPosition(carro.getPosition() + (vDirecao*velocidade));

    camera.setView(carro.getPosition());
}

void onKeyDown(int key){

    if (key == S_KEY_LEFT){
        left = true;
    }
    if (key == S_KEY_RIGHT){
        right = true;
    }
    if (key == S_KEY_UP){
        up = true;
    }
    if (key == S_KEY_DOWN){
        down = true;
    }
}

void onKeyUp(int key){

    if (key == S_KEY_LEFT){
        left = false;
    }
    if (key == S_KEY_RIGHT){
        right = false;
    }
    if (key == S_KEY_UP){
        up = false;
    }
    if (key == S_KEY_DOWN){
        down = false;
    }
}

void onTouchStart(int pointer, float x, float y){
    analogCenter.x = x;
    analogCenter.y = y;
}

void onTouchDrag(int pointer, float x, float y){

    left = false;
    right = false;
    up = false;
    down = false;

    if ((x - analogCenter.x) > 40){
        right = true;
    }

    if ((analogCenter.x - x) > 40){
        left = true;
    }

    if ((analogCenter.y - y) > 40){
        up = true;
    }

    if ((y - analogCenter.y) > 40){
        down = true;
    }
}

void onTouchEnd(int pointer, float x, float y){
    analogCenter.x = 0;
    analogCenter.y = 0;

    left = false;
    right = false;
    up = false;
    down = false;
}
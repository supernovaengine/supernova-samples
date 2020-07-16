#include "Supernova.h"

#include "Scene.h"
#include "Terrain.h"
#include "Input.h"
#include "Cube.h"
#include "Text.h"
#include "Log.h"
#include "DirectionalLight.h"
#include "System.h"

using namespace Supernova;
Scene cena;
Scene cena2;
Camera camera;
Terrain plano;
Cube cubo (10,10,10);
Cube cubo2 (10,10,10);
Cube cubo3 (10,10,10);
Cube cubo4 (10,10,10);
Text texto;
Text texto2;
Text texto3;
Text texto4;

float ultimoX;
float ultimoY;
float ultimoPressX;
float ultimoPressY;

void onUpdate();
void onTouchStart(int pointer, float x, float y);
void onTouchDrag(int pointer, float x, float y);

void onKeyDown(int key){
    if (key == S_KEY_X){
        camera.setPosition(camera.getPosition().x, camera.getPosition().y+10, camera.getPosition().z);
        camera.setView(camera.getView().x, camera.getView().y+10, camera.getView().z);
    }

    if (key == S_KEY_Z){
        camera.setPosition(camera.getPosition().x, camera.getPosition().y-10, camera.getPosition().z);
        camera.setView(camera.getView().x, camera.getView().y-10, camera.getView().z);
    }
}

void onKeyUp(int key){
    if (key == S_KEY_F){
        if (!System::instance().isFullscreen()) {
            System::instance().requestFullscreen();
        }else{
            System::instance().exitFullscreen();
        }
    }
}

void onMouseMove(float x, float y) {
    //Log::Debug("Mouse %f %f", x, y);
}

void init(){
    Engine::setCanvasSize(1000,480);
    Engine::setCallTouchInMouseEvent(true);
    //Engine::setScalingMode(Scaling::STRETCH);

    camera.setPosition(0, 150, -600);

    plano.setTexture("ground.png");
    plano.setHeightMap("HeightMap.png");
    plano.setBlendMap("blendmap.png");
    plano.addTextureDetail("block.png", BlendMapColor::BLUE);
    //plano.setPosition(100,0,1200);
    //plano.setScale(Vector3(1.5,1,1.5));

    cena.setAmbientLight(0.2);

    DirectionalLight* sol = new DirectionalLight();
    sol->setDirection(0,-0.3,-0.8);
    sol->setShadow(true);
    cena.addObject(sol);

    cubo.setCenter(5,5,5);
    cubo.setColor(0.8,0.2,0.2,1.0);
    cubo.setPosition(629, 0, -158);

    cubo2.setCenter(5,5,5);
    cubo2.setColor(0.2,0.8,0.2,1.0);
    cubo2.setPosition(cubo.getPosition().x+32, cubo.getPosition().y, cubo.getPosition().z);
    cubo3.setCenter(5,5,5);
    cubo3.setColor(0.2,0.2,0.8,1.0);
    cubo3.setPosition(cubo.getPosition().x+95, cubo.getPosition().y, cubo.getPosition().z);
    cubo4.setCenter(5,5,5);
    cubo4.setColor(0.2,0.8,0.8,1.0);
    cubo4.setPosition(cubo.getPosition().x+222, cubo.getPosition().y, cubo.getPosition().z);

    cena.addObject(&plano);
    cena.setCamera(&camera);
    //cena.addObject(&cubo);
    //cena.addObject(&cubo2);
    //cena.addObject(&cubo3);
    //cena.addObject(&cubo4);

    texto.setText("Texto");
    texto.setPosition(100, 100, 0);
    texto2.setPosition(100, 150, 0);
    texto3.setPosition(100, 200, 0);
    texto4.setPosition(100, 250, 0);
    //texto.setWidth(200);
    cena2.addObject(&texto);
    cena2.addObject(&texto2);
    cena2.addObject(&texto3);
    cena2.addObject(&texto4);

    cena.addObject(&cena2);

    Engine::setScene(&cena);

    Engine::onTouchStart = onTouchStart;
    Engine::onTouchDrag = onTouchDrag;
    Engine::onUpdate = onUpdate;
    Engine::onKeyDown = onKeyDown;
    Engine::onKeyUp = onKeyUp;
    Engine::onMouseMove = onMouseMove;
}

void onTouchStart(int pointer, float x, float y) {
    ultimoX = x;
    ultimoY = y;
    ultimoPressX = x;
    ultimoPressY = y;
}

void onTouchDrag(int pointer, float x, float y) {
    float difX = ultimoX - x;
    ultimoX = x;
    camera.rotateView(0.1 * difX);

    float difY = ultimoY - y;
    ultimoY = y;
    camera.elevateView(-0.1 * difY);
}

void onUpdate(){
    texto.setText(std::string("FPS: ") + std::to_string(Engine::getFramerate()).c_str());
    texto2.setText(std::string("Camera X: ") + std::to_string(camera.getWorldPosition().x));
    texto3.setText(std::string("Camera Y: ") + std::to_string(camera.getWorldPosition().y));
    texto4.setText(std::string("Camera Z: ") + std::to_string(camera.getWorldPosition().z));

    if (Input::isKeyPressed(S_KEY_UP) or Input::isKeyPressed(S_KEY_UP)){
        camera.walkForward(10);
    }
    if (Input::isKeyPressed(S_KEY_DOWN) or Input::isKeyPressed(S_KEY_S)){
        camera.walkForward(-10);
    }
    if (Input::isKeyPressed(S_KEY_LEFT)){
        camera.rotateView(1);
    }
    if (Input::isKeyPressed(S_KEY_RIGHT)){
        camera.rotateView(-1);
    }
    if (Input::isKeyPressed(S_KEY_A)){
        camera.slide(-1);
    }
    if (Input::isKeyPressed(S_KEY_D)){
        camera.slide(1);
    }

    //if (Input::isKeyPressed(S_KEY_X)){
    //    camera.setPosition(camera.getPosition().x, camera.getPosition().y+1, camera.getPosition().z);
    //    camera.setView(camera.getView().x, camera.getView().y+1, camera.getView().z);
    //}
    //if (Input::isKeyPressed(S_KEY_Z)){
    //    camera.setPosition(camera.getPosition().x, camera.getPosition().y-1, camera.getPosition().z);
    //    camera.setView(camera.getView().x, camera.getView().y-1, camera.getView().z);
    //}

}
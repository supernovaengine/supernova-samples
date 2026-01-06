#include "Supernova.h"

using namespace Supernova;

void onUpdate();
void onKeyDown(int key, bool repeat, int mods);
void onTouchStart(int pointer, float x, float y);
void onTouchMove(int pointer, float x, float y);

Vector2 lastTouchPos;

Scene scene;

Model model(&scene);
Camera camera(&scene);
Shape terrain(&scene);
SkyBox sky(&scene);
Light sun(&scene);

Camera cameramirror(&scene);
Sprite mirror(&scene);


SUPERNOVA_INIT void init(){
    scene.setCamera(camera.getEntity());
    scene.setGlobalIllumination(0.5);

    camera.setPosition(0, 7, 40);
    camera.setName("camera");

    sun.setType(LightType::DIRECTIONAL);
    sun.setDirection(0, -0.4, -0.6);

    terrain.createPlane(200, 200);
    terrain.setTexture("ground.png");
    terrain.setName("terrain");

    cameramirror.setPosition(0, 5, 0);
    cameramirror.setTarget(0, 5, 40);
    cameramirror.setRenderToTexture(true);
    cameramirror.setName("cameramirror");

    mirror.setTexture(cameramirror.getFramebuffer());
    mirror.setSize(10,10);
    mirror.setPivotPreset(PivotPreset::CENTER);
    mirror.setPosition(0,5,0);
    mirror.setName("mirror");

    model.loadModel("WaterBottle.glb");
    model.setScale(20);
    model.setPosition(0,3,20);

    sky.setTextureFront("ely_hills/hills_lf.tga");
    sky.setTextureBack("ely_hills/hills_rt.tga");
    sky.setTextureLeft("ely_hills/hills_bk.tga");
    sky.setTextureRight("ely_hills/hills_ft.tga");
    sky.setTextureUp("ely_hills/hills_up.tga");
    sky.setTextureDown("ely_hills/hills_dn.tga");

    Engine::setScene(&scene);
    Engine::setCallTouchInMouseEvent(true);

    Engine::onUpdate = onUpdate;
    Engine::onKeyDown = onKeyDown;
    Engine::onTouchStart = onTouchStart;
    Engine::onTouchMove = onTouchMove;
}

void onUpdate(){

    if (Input::isKeyPressed(S_KEY_UP) || Input::isKeyPressed(S_KEY_W)){
        camera.walkForward(1);
    }else if (Input::isKeyPressed(S_KEY_DOWN) || Input::isKeyPressed(S_KEY_S)){
        camera.walkForward(-1);
    }

    if (Input::isKeyPressed(S_KEY_A)){
        camera.slide(-1);
    }else if (Input::isKeyPressed(S_KEY_D)){
        camera.slide(1);
    }

    if (Input::isKeyPressed(S_KEY_LEFT)){
        camera.rotateView(2);
    }else if (Input::isKeyPressed(S_KEY_RIGHT)){
        camera.rotateView(-2);
    }

    // necessary if use camera.getWorldPosition() to update world positions
    // scene.getSystem<RenderSystem>()->updateTransform(camera.getComponent<Transform>());

    Vector3 camVec = mirror.getPosition() - camera.getPosition();
    Vector3 reflVec = camVec.reflect(Vector3(0,0,1));
    cameramirror.setTarget(cameramirror.getPosition() + reflVec);
}

void onKeyDown(int key, bool repeat, int mods){

}

void onTouchMove(int pointer, float x, float y){
    float difX = lastTouchPos.x - x;
    float difY = lastTouchPos.y - y;
    lastTouchPos = Vector2(x, y);

    camera.rotateView(0.1 * difX);
    camera.elevateView(0.1 * difY);
}

void onTouchStart(int pointer, float x, float y){
    lastTouchPos = Vector2(x, y);
}

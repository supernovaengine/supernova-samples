
#include "Supernova.h"
#include "Scene.h"

#include "Camera.h"
#include "PlaneTerrain.h"
#include "Image.h"
#include "Model.h"
#include "SkyBox.h"
#include "Container.h"
#include "Text.h"
#include "Input.h"
#include "Angle.h"

using namespace Supernova;

Scene scene;
Image image(&scene);
Container textcontainer(&scene);
Text text1(&scene);
Text text2(&scene);

Scene carscene;
Camera* camera;
PlaneTerrain terrain(&carscene);
Model car(&carscene);
SkyBox sky(&carscene);

float curve = 0;
float speed = 0;
float rotation = 0;

void onUpdate();
void onKeyDown(int key, bool repeat, int mods);

void init(){
    Engine::setCanvasSize(1000, 480);
    Engine::setCallTouchInMouseEvent(true);

    camera = new Camera(&carscene);

    camera->setFramebufferFilter(TextureFilter::NEAREST);
    camera->setFramebufferSize(512, 512);
    camera->setRenderToTexture(true);
    camera->setPosition(0, 5, 20);
    carscene.setCamera(camera->getEntity());

    terrain.create(200, 200);
    terrain.setTexture("road.png");
    terrain.setPosition(-100,0,-100);

    car.loadModel("jeep/Jeep.obj");
    car.setScale(0.5);

    sky.setTextureFront("ely_hills/hills_lf.tga");
    sky.setTextureBack("ely_hills/hills_rt.tga");
    sky.setTextureLeft("ely_hills/hills_bk.tga");
    sky.setTextureRight("ely_hills/hills_ft.tga");
    sky.setTextureUp("ely_hills/hills_up.tga");
    sky.setTextureDown("ely_hills/hills_dn.tga");

    image.setTexture(camera->getFramebuffer());
    image.setPosition(550,100,0);
    image.setSize(400, 300);
    image.setAnchorPreset(AnchorPreset::CENTER);

    textcontainer.setAnchorPreset(AnchorPreset::CENTER_TOP);
    textcontainer.addChild(&text1);
    textcontainer.addChild(&text2);

    text1.setText("Press F to fullscreen draw rect");
    text1.setFontSize(20);
    text1.setAnchorPreset(AnchorPreset::CENTER);
    text2.setText("Press R to change resolution");
    text2.setFontSize(20);
    text2.setAnchorPreset(AnchorPreset::CENTER);

    Engine::setScene(&scene);
    Engine::addSceneLayer(&carscene);
    Engine::setScalingMode(Scaling::NATIVE);

    Engine::onKeyDown = onKeyDown;
    Engine::onUpdate = onUpdate;

}

void onKeyDown(int key, bool repeat, int mods){
    if (key == S_KEY_F){
        if (image.getAnchorPreset() == AnchorPreset::CENTER){
            image.setAnchorPreset(AnchorPreset::FULL_LAYOUT);
        }else{
            image.setSize(400, 300);
            image.setAnchorPreset(AnchorPreset::CENTER);
        }
    }
    if (key == S_KEY_R){
        if (camera->getFramebuffer()->getWidth() == 512){
            camera->setFramebufferSize(256, 256);
        }else{
            camera->setFramebufferSize(512, 512);
        }
    }
}

void onUpdate(){
    if (Input::isKeyPressed(S_KEY_UP)){
        speed += 0.1;
    }else if (Input::isKeyPressed(S_KEY_DOWN)){
        speed -= 0.1;
    }
    speed *= 0.95;

    if (Input::isKeyPressed(S_KEY_LEFT)){
        if (curve < 3)
            curve += 0.4;
    }else if (Input::isKeyPressed(S_KEY_RIGHT)){
        if (curve > -3)
            curve -= 0.4;
    }else{
        curve = 0;
    }

    rotation += curve;
    if (rotation > 360)
        rotation = rotation - 360;
    if (rotation < 0)
        rotation = 360 + rotation;

    Vector3 vDir(cos(Angle::degToRad(rotation-90)), 0, -sin(Angle::degToRad(rotation-90)));

    car.setRotation(0,rotation,0);
    car.setPosition(car.getPosition() + (vDir*speed));

    camera->setView(car.getPosition());
}

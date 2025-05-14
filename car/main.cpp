#include "Supernova.h"


using namespace Supernova;

Scene scene;
Scene uiscene;

Camera camera(&scene);
Shape terrain(&scene);

Model car(&scene);

Model house(&scene);
SkyBox sky(&scene);
Audio carengine(&scene);
Fog fog(&scene);

Light* carlight = NULL;
Light* sun = NULL;

Text text(&uiscene);

float curve = 0;
float speed = 0;
float rotation = 0;

bool up, down, left, right;

void onUpdate();

void init(){

    scene.setGlobalIllumination(0.3);
    scene.setBackgroundColor(0.8, 0.8, 0.8);

    scene.setCamera(camera.getEntity());

    fog.setType(FogType::LINEAR);
    fog.setLinearStart(30);
    fog.setLinearEnd(100);

    camera.setPosition(0, 5, 20);

    house.loadModel("old-house/old-house.obj");
    house.setRotation(-1,2,0);
    house.setRotation(-90,180,0);
    house.setPosition(6,0,6);

    terrain.createPlane(200, 200);
    terrain.setTexture("road.png");

    car.loadModel("jeep/Jeep.obj");
    car.setScale(0.5);
    car.addChild(&carengine);

    carengine.loadAudio("engine.wav");
    carengine.setSound3D(true);
    carengine.setLopping(true);
    carengine.setDopplerFactor(10.0);
    carengine.setMinMaxDistance(1, 100);
    carengine.setAttenuationModel(AudioAttenuation::LINEAR_DISTANCE);
    carengine.play();

    sky.setTextureFront("ely_hills/hills_lf.tga");
    sky.setTextureBack("ely_hills/hills_rt.tga");
    sky.setTextureLeft("ely_hills/hills_bk.tga");
    sky.setTextureRight("ely_hills/hills_ft.tga");
    sky.setTextureUp("ely_hills/hills_up.tga");
    sky.setTextureDown("ely_hills/hills_dn.tga");
    sky.setAlpha(0.2);

    if (!carlight)
        carlight = new Light(&scene);
    carlight->setType(LightType::SPOT);
    carlight->setConeAngle(80, 100);
    carlight->setPosition(0, 5, 8);
    carlight->setDirection(0, 0, 30);
    carlight->setIntensity(50);
    carlight->setShadows(true);
    car.addChild(carlight);

    if (!sun)
        sun = new Light(&scene);
    sun->setType(LightType::DIRECTIONAL);
    sun->setDirection(0, -0.4, 0.6);
    sun->setShadows(true);

    text.setPosition(100, 100, 0);

    Engine::setScene(&scene);
    Engine::addSceneLayer(&uiscene);

    Engine::onUpdate = onUpdate;
}

void onUpdate(){

    text.setText(std::to_string(Engine::getFramerate()).c_str());

    if (Input::isKeyPressed(S_KEY_UP)){
        speed += 0.1;
    }else if (Input::isKeyPressed(S_KEY_DOWN)){
        speed -= 0.1;
    }
    speed *= 0.95;

    carengine.setVolume(1.0 + (abs(speed) * 0.5));
    carengine.setSpeed(1.0 + (abs(speed) * 0.5));

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

    camera.setTarget(car.getPosition());
}

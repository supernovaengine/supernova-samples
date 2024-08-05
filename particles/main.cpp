#include "Supernova.h"
using namespace Supernova;

enum class ParticlesType{
    POINTS,
    SPRITES
};

std::string parttext(" particles (press any key to change)");

Scene scene;

Text text(&scene);

Points points(&scene);
Sprite sprite(&scene);
Particles particles(&scene);

ParticlesType type;

void onKeyDown(int key, bool repeat, int mods);

void init(){
    text.setAnchorPreset(AnchorPreset::CENTER_TOP);

    text.setText("Sprite" + parttext);
    type = ParticlesType::SPRITES;

    sprite.setPosition(300, 100, 0);
    sprite.setPivotPreset(PivotPreset::CENTER);
    sprite.setTexture("explosion.png");
    sprite.setSize(50, 50);
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            sprite.addFrame((i+(j*3)), "", Rect(i * ((1/3.0)), j * ((1/3.0)), (1/3.0), (1/3.0)));
        }
    }

    points.setPosition(300, 100, 0);
    points.setTexture("explosion.png");
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            points.addSpriteFrame((i+(j*3)), "", Rect(i * ((1/3.0)), j * ((1/3.0)), (1/3.0), (1/3.0)));
        }
    }

    //particles.addParticle(Vector3(30, 30, 0), Vector4(1.0, 1.0, 1.0, 1.0), 50, 40);
    //particles.addParticle(Vector3(20, 60, 0), Vector4(0.0, 1.0, 0.0, 1.0), 40, 0, Rect(0, 0, 0.5, 0.5));

    particles.setTarget(&sprite);

    particles.setLifeInitializer(10);

    particles.setPositionInitializer(Vector3(0,0,0), Vector3(300,0,0));
    //particles.setPositionModifier(2,4, Vector3(0,0,0), Vector3(0,300,0));

    particles.setVelocityInitializer(Vector3(0,10,0), Vector3(0,50,0));
    particles.setVelocityModifier(5, 8, Vector3(0,10,0), Vector3(0,300,0), EaseType::CUBIC_IN_OUT);

    //particles.setAccelerationInitializer(Vector3(0,100,0), Vector3(0,200,0));

    particles.setColorInitializer(Vector3(0,0,0), Vector3(1,1,1));
    //particles.setColorModifier(2, 5, Vector3(1,1,1), Vector3(1,0,0));

    //particles.setAlphaInitializer(0, 1);
    particles.setAlphaModifier(4, 6, 1, 0.2);

    particles.setSizeInitializer(10, 50); //for points
    particles.setScaleInitializer(1.0/5.0, 1.0);

    particles.setSpriteIntializer(0, 2);
    particles.setSpriteModifier(1, 8, {0,1,2,3,4,5,6,7,8});

    //particles.setRotationInitializer(0, 90);
    //particles.setRotationModifier(1, 5, 0, 359);

    Engine::setScene(&scene);
    Engine::onKeyDown = onKeyDown;

    particles.start();
}

void onKeyDown(int key, bool repeat, int mods){
    if (type == ParticlesType::SPRITES){
        text.setText("Points" + parttext);
        type = ParticlesType::POINTS;
        particles.setTarget(&points);

        sprite.clearInstances();
        sprite.setVisible(false);
        points.setVisible(true);
    }else{
        text.setText("Sprite" + parttext);
        type = ParticlesType::SPRITES;
        particles.setTarget(&sprite);

        points.clearPoints();
        points.setVisible(false);
        sprite.setVisible(true);
    }
}
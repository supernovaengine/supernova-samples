#include "Supernova.h"
using namespace Supernova;


#include "Particles.h"
#include "ParticlesAnimation.h"

Scene scene;

Particles particles(&scene);
ParticlesAnimation partianim(&scene);

void init(){

    particles.setPosition(300, 100, 0);
    particles.setTexture("f4.png");

    //particles.addParticle(Vector3(30, 30, 0), Vector4(1.0, 1.0, 1.0, 1.0), 50, 40);
    //particles.addParticle(Vector3(20, 60, 0), Vector4(0.0, 1.0, 0.0, 1.0), 40, 0, Rect(0, 0, 0.5, 0.5));
    
    //particles.addSpriteFrame(0, "", Rect(0.5, 0.5, 0.5, 0.5));
    //particles.addSpriteFrame(1, "", Rect(0.5, 0.0, 0.5, 0.5));
    //particles.addSpriteFrame(2, "", Rect(0.0, 0.5, 0.5, 0.5));

    partianim.setTarget(particles.getEntity());

    partianim.setLifeInitializer(10);

    partianim.setPositionInitializer(Vector3(0,0,0), Vector3(300,0,0));
    //partianim.setPositionModifier(2,4, Vector3(0,0,0), Vector3(0,300,0));

    partianim.setVelocityInitializer(Vector3(0,10,0), Vector3(0,50,0));
    partianim.setVelocityModifier(5, 8, Vector3(0,10,0), Vector3(0,300,0), EaseType::CUBIC_IN_OUT);

    //partianim.setAccelerationInitializer(Vector3(0,100,0), Vector3(0,200,0));

    partianim.setColorInitializer(Vector3(0,0,0), Vector3(1,1,1));
    //partianim.setColorModifier(2, 5, Vector3(1,1,1), Vector3(1,0,0));

    //partianim.setAlphaInitializer(0, 1);
    partianim.setAlphaModifier(4, 6, 1, 0.2);

    partianim.setSizeInitializer(10, 50);

    //partianim.setSpriteIntializer(0, 2);
    //partianim.setSpriteModifier(5, 8, {0,1,2});

    //partianim.setRotationInitializer(90);
    //partianim.setRotationModifier(1, 5, 0, 360);

    //Engine::setScene(&scene);

    //partianim.start();
}
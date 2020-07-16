#include "Supernova.h"

#include "Scene.h"
#include "Polygon.h"
#include "Camera.h"
#include "Particles.h"
#include "ParticlesAnimation.h"
#include "ParticleVelocityInit.h"
#include "ParticleLifeInit.h"
#include "ParticleSizeInit.h"
#include "ParticleColorInit.h"
#include "ParticleAccelerationInit.h"
#include "ParticlePositionInit.h"
#include "ParticleRotationInit.h"
#include "ParticleSpriteInit.h"
#include "ParticleVelocityMod.h"
#include "ParticleRotationMod.h"
#include "ParticleSpriteMod.h"
#include "ParticleAlphaMod.h"
#include "ParticleSizeMod.h"


using namespace Supernova;

Scene scene;
Particles particles;
ParticlesAnimation* particlesanim;
ParticlePositionInit* posInit;

void onTouchStart(int pointer, float x, float y);
void onTouchDrag(int pointer, float x, float y);

void init(){
    Engine::setCanvasSize(1280, 720);

    Engine::setCallTouchInMouseEvent(true);

    posInit = new ParticlePositionInit(Vector3(100,100,0));

    particlesanim = new ParticlesAnimation();
    particlesanim->addInit(new ParticleVelocityInit(Vector3(-15,-4, 0),Vector3(15,24, 0)));
    particlesanim->addInit(new ParticleLifeInit(10));
    particlesanim->addInit(new ParticleSizeInit(50, 100));
    //particlesanim->addInit(new ParticleRotationInit(0, 180));
    particlesanim->addInit(new ParticleColorInit(0,0,0,1,1,0));
    //particlesanim->addInit(new ParticleAccelerationInit(Vector3(0.0f,9.81f * 5, 0.0f)));
    particlesanim->addInit(posInit);

    std::vector<int> sprites;
    sprites.push_back(1);
    //sprites.push_back(0);
    //sprites.push_back(2);
    //particlesanim->addInit(new ParticleSpriteInit(sprites));
    //particlesanim->addInit(new ParticleSpriteInit(2));

    //particlesanim->addMod(new ParticleVelocityMod(7, 2, Vector3(0,500,0), Vector3(0,0,0)));
    //particlesanim->addMod(new ParticleRotationMod(10, 0, 0, 360));
    //particlesanim->addMod(new ParticleAlphaMod(10, 0, 1, 0));
    //particlesanim->addMod(new ParticleSizeMod(10, 0, 100, 200));

    //particlesanim->addMod(new ParticleSpriteMod(10, 9, 0));
    //particlesanim->addMod(new ParticleSpriteMod(10, 0, 0, 3));
    //particlesanim->addMod(new ParticleSpriteMod(1, 0, 1));

    particles.setPosition(0,0,0);
    particles.addAction(particlesanim);
    particles.setRate(10);
    particles.setMaxParticles(100);
    particles.setTexture("f4.png");
    //particles.addSpriteFrame("1", 1, 1, 256, 256);
    //particles.addSpriteFrame("2", 1, 256, 256, 256);
    //particles.addSpriteFrame("3", 256, 256, 256, 256);
    //particles.addSpriteFrame("4", 256, 1, 256, 256);
    //particles.useSpriteFrames(true);

    scene.addObject(&particles);

    particlesanim->run();

    Engine::setScene(&scene);
    Engine::onTouchStart = onTouchStart;
    Engine::onTouchDrag = onTouchDrag;
}

void onTouchStart(int pointer, float x, float y){
    //if (particlesanim->isRunning())
    //    particlesanim->pause();
    //else
    //    particlesanim->run();
    posInit->setPosition(Vector3(x, y, 0));
}

void onTouchDrag(int pointer, float x, float y){
    posInit->setPosition(Vector3(x, y, 0));
}
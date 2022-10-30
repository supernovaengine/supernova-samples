scene = Scene()

particles = Particles(scene)
partianim = ParticlesAnimation(scene)


particles:setPosition(300, 100, 0);
particles:setTexture("f4.png");


partianim.target = particles.entity

partianim:setLifeInitializer(10)

partianim:setPositionInitializer(Vector3(0,0,0), Vector3(300,0,0))
--partianim:setPositionModifier(2,4, Vector3(0,0,0), Vector3(0,300,0))

partianim:setVelocityInitializer(Vector3(0,10,0), Vector3(0,50,0))
partianim:setVelocityModifier(5, 8, Vector3(0,10,0), Vector3(0,300,0), EaseType.CUBIC_IN_OUT)

--partianim:setAccelerationInitializer(Vector3(0,100,0), Vector3(0,200,0))

partianim:setColorInitializer(Vector3(0,0,0), Vector3(1,1,1))
--partianim:setColorModifier(2, 5, Vector3(1,1,1), Vector3(1,0,0))

--partianim:setAlphaInitializer(0, 1)
partianim:setAlphaModifier(4, 6, 1, 0.2)

partianim:setSizeInitializer(10, 50)

--partianim:setSpriteIntializer(0, 2)
--partianim:setSpriteModifier(5, 8, {0,1,2})

--partianim:setRotationInitializer(90)
--partianim:setRotationModifier(1, 5, 0, 360)

Engine.setScene(scene)

partianim:start()
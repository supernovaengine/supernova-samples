scene = Scene()

ParticlesType = {
    POINTS = 0,
    SPRITES = 1
}

parttext = " particles (press any key to change)"

text = Text(scene)

points = Points(scene)
sprite = Sprite(scene)
particles = Particles(scene)


function onKeyDown(key, rep, mods)
    if type == ParticlesType.SPRITES then
        text.text = "Points"..parttext
        type = ParticlesType.POINTS
        particles.target = points.entity

        sprite:clearInstances()
        sprite.visible = false
        points.visible = true
    else
        text.text = "Sprite"..parttext
        type = ParticlesType.SPRITES
        particles.target = sprite.entity

        points:clearPoints()
        points.visible = false
        sprite.visible = true
    end
end


text.anchorPreset = AnchorPreset.CENTER_TOP

text.text = "Sprite"..parttext
type = ParticlesType.SPRITES

sprite:setPosition(300, 100, 0);
sprite.pivotPreset = PivotPreset.CENTER;
sprite:setTexture("explosion.png");
sprite:setSize(50, 50);
for i = 0,3,1 do
    for j = 0,3,1 do
        sprite:addFrame((i+(j*3)), "", Rect(i * ((1/3.0)), j * ((1/3.0)), (1/3.0), (1/3.0)));
    end
end

points:setPosition(300, 100, 0)
points:setTexture("explosion.png")
for i = 0,3,1 do
    for j = 0,3,1 do
        points:addSpriteFrame((i+(j*3)), "", Rect(i * ((1/3.0)), j * ((1/3.0)), (1/3.0), (1/3.0)));
    end
end


particles.target = sprite.entity

particles:setLifeInitializer(10)

particles:setPositionInitializer(Vector3(0,0,0), Vector3(300,0,0))
--particles:setPositionModifier(2,4, Vector3(0,0,0), Vector3(0,300,0))

particles:setVelocityInitializer(Vector3(0,10,0), Vector3(0,50,0))
particles:setVelocityModifier(5, 8, Vector3(0,10,0), Vector3(0,300,0), EaseType.CUBIC_IN_OUT)

--particles:setAccelerationInitializer(Vector3(0,100,0), Vector3(0,200,0))

particles:setColorInitializer(Vector3(0,0,0), Vector3(1,1,1))
--particles:setColorModifier(2, 5, Vector3(1,1,1), Vector3(1,0,0))

--particles:setAlphaInitializer(0, 1)
particles:setAlphaModifier(4, 6, 1, 0.2)

particles:setSizeInitializer(10, 50)
particles:setScaleInitializer(1.0/5.0, 1.0)

particles:setSpriteIntializer(0, 2)
particles:setSpriteModifier(1, 8, {0,1,2,3,4,5,6,7,8})

--particles:setRotationInitializer(90)
--particles:setRotationModifier(1, 5, 0, 360)

Engine.setScene(scene)
Engine.onKeyDown = onKeyDown

particles:start()
scene = Scene()

camera = Camera(scene)
terrain = Mesh(scene)
model = Model(scene)
sky = SkyBox(scene)
sun = Light(scene);

function onKeyDown(key, rep, mods)
    model:getAnimation(0):start()
end

function onTouchStart(pointer, x, y)
    model:getAnimation(0):start()
end

scene.ambientLightFactor = 0.2
scene.camera = camera.entity

camera:setPosition(0, 7, -20)

terrain:createPlane(200, 200)
terrain:setTexture("ground.png")

model:loadModel("AnimatedMorphCube.gltf")
model:setScale(100)
model:setPosition(0,1,0)
model:setRotation(0,90,0)
model:getAnimation(0).loop = true

sun.type = LightType.DIRECTIONAL
sun:setDirection(0,-0.7, 0.8)
sun:setShadows(true)

sky:setTextureFront("ely_hills/hills_lf.tga")
sky:setTextureBack("ely_hills/hills_rt.tga")
sky:setTextureLeft("ely_hills/hills_bk.tga")
sky:setTextureRight("ely_hills/hills_ft.tga")
sky:setTextureUp("ely_hills/hills_up.tga")
sky:setTextureDown("ely_hills/hills_dn.tga")

Engine.scalingMode = Scaling.FITWIDTH 
Engine.setCanvasSize(1000, 480)
Engine.setScene(scene);
Engine.callTouchInMouseEvent = true

Engine.onKeyDown = onKeyDown
Engine.onTouchStart = onTouchStart
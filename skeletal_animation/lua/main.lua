lastTouchPos = Vector2(0, 0)

scene = Scene()

camera = Camera(scene)
terrain = Shape(scene)
model = Model(scene)
sky = SkyBox(scene)
sun = Light(scene)

uiscene = Scene()
text = Text(uiscene)

function onKeyDown(key, rep, mods)
    model:getAnimation(0):start()
end

function onTouchStart(pointer, x, y)
    lastTouchPos = Vector2(x, y)
end

function onTouchMove(pointer, x, y)
    difX = lastTouchPos.x - x
    difY = lastTouchPos.y - y
    lastTouchPos = Vector2(x, y)

    camera:rotatePosition(0.1 * difX)
    camera:elevatePosition(-0.1 * difY)
end

scene.globalIlluminationIntensity = 0.1
scene.camera = camera.entity

text.text = "Press any key to start"
text.anchorPreset = AnchorPreset.CENTER_TOP

camera:setPosition(0, 7, -20)
camera:setTarget(0, 2, 0);

terrain:createPlane(200, 200)
terrain:setTexture("ground.png")

model:loadModel("CesiumMan.glb")
model:setScale(4)
model:setRotation(-90,0,0)
model:getAnimation(0).loop = true

sun.type = LightType.DIRECTIONAL
sun:setDirection(0,-0.7, 0.8)
sun:setIntensity(10)
sun:setShadows(true)

sky:setTextureNegativeZ("ely_hills/hills_lf.tga")
sky:setTexturePositiveZ("ely_hills/hills_rt.tga")
sky:setTextureNegativeX("ely_hills/hills_bk.tga")
sky:setTexturePositiveX("ely_hills/hills_ft.tga")
sky:setTextureNegativeY("ely_hills/hills_dn.tga")
sky:setTexturePositiveY("ely_hills/hills_up.tga")

Engine.scalingMode = Scaling.FITWIDTH 
Engine.setCanvasSize(1000, 480)
Engine.setScene(scene)
Engine.addSceneLayer(uiscene)
Engine.callTouchInMouseEvent = true

Engine.onKeyDown = onKeyDown
Engine.onTouchStart = onTouchStart
Engine.onTouchMove = onTouchMove
scene = Scene()
uiscene = Scene()

camera = Camera(scene)
terrain = Shape(scene)
car = Model(scene)
house = Model(scene)
sky = SkyBox(scene)
carengine = Audio(scene)
fog = Fog(scene)

text = Text(uiscene)

curve = 0
speed = 0
rotation = 0

up, down, left, right = false

function onUpdate()

    text.text = tostring(Engine.framerate)

    if (Input.isKeyPressed(Input.KEY_UP)) then
        speed = speed + 0.1
    elseif (Input.isKeyPressed(Input.KEY_DOWN)) then
        speed = speed - 0.1
    end
    speed = speed * 0.95

    carengine.volume = 1.0 + (math.abs(speed) * 0.5)
    carengine.speed = 1.0 + (math.abs(speed) * 0.5)

    if (Input.isKeyPressed(Input.KEY_LEFT)) then
        if (curve < 3) then
            curve = curve + 0.4
        end
    elseif (Input.isKeyPressed(Input.KEY_RIGHT)) then
        if (curve > -3) then
            curve = curve - 0.4
        end
    else
        curve = 0
    end

    rotation = rotation + curve
    if (rotation > 360) then
        rotation = rotation - 360
    end
    if (rotation < 0) then
        rotation = 360 + rotation
    end

    vDir = Vector3(math.cos(Angle.degToRad(rotation-90)), 0, -math.sin(Angle.degToRad(rotation-90)))

    car:setRotation(0, rotation, 0);
    car.position = car.position + (vDir*speed)

    camera.view = car.position
end


scene.camera = camera.entity

scene.ambientLightFactor = 0.5;
scene:setBackgroundColor(0.8, 0.8, 0.8);

fog.type = FogType.LINEAR
fog.linearStart = 30
fog.linearEnd = 100

camera:setPosition(0, 5, 20)

house:loadModel("old-house/old-house.obj")
house:setRotation(-1,2,0)
house:setRotation(-90,180,0)
house:setPosition(6,0,6)

terrain:createPlane(200, 200)
terrain:setTexture("road.png")

car:loadModel("jeep/Jeep.obj")
car:setScale(0.5)
car:addChild(carengine)

carengine:loadAudio("engine.wav")
carengine.sound3D = true
carengine.lopping = true
carengine.dopplerFactor = 10.0
carengine:setMinMaxDistance(1, 100)
carengine.attenuationModel = AudioAttenuation.LINEAR_DISTANCE
carengine:play()

sky:setTextureFront("ely_hills/hills_lf.tga")
sky:setTextureBack("ely_hills/hills_rt.tga")
sky:setTextureLeft("ely_hills/hills_bk.tga")
sky:setTextureRight("ely_hills/hills_ft.tga")
sky:setTextureUp("ely_hills/hills_up.tga")
sky:setTextureDown("ely_hills/hills_dn.tga")
sky.alpha = 0.2

carlight = Light(scene)
carlight.type = LightType.SPOT
carlight:setConeAngle(80, 100)
carlight:setPosition(0, 5, 8)
carlight:setDirection(0, 0, 30)
carlight.intensity = 50
carlight.shadows = true
car:addChild(carlight)

sun = Light(scene);
sun.type = LightType.DIRECTIONAL
sun:setDirection(0, -0.4, 0.6)
sun.shadows = true

text:setPosition(100, 100, 0)

Engine.setScene(scene)
Engine.addSceneLayer(uiscene)

Engine.onUpdate = onUpdate

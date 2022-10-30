lastX = 0
lastY = 0
lastPressX = 0
lastPressY = 0

scene = Scene()
uiscene = Scene()

camera = Camera(scene)
terrain = Terrain(scene)
sun = Light(scene)

text = Text(uiscene)
text2 = Text(uiscene)
text3 = Text(uiscene)
text4 = Text(uiscene)


function onUpdate()
    text.text = "FPS: " .. tostring(Engine.framerate)
    text2.text = "Camera X: " .. tostring(camera.position.x)
    text3.text = "Camera Y: " .. tostring(camera.position.y)
    text4.text = "Camera Z: " .. tostring(camera.position.z)

    if (Input.isKeyPressed(Input.KEY_UP) or Input.isKeyPressed(Input.KEY_UP)) then
        camera:walkForward(1)
    end
    if (Input.isKeyPressed(Input.KEY_DOWN) or Input.isKeyPressed(Input.KEY_S)) then
        camera:walkForward(-1)
    end
    if Input.isKeyPressed(Input.KEY_LEFT) then
        camera:rotateView(1)
    end
    if Input.isKeyPressed(Input.KEY_RIGHT) then
        camera:rotateView(-1)
    end
    if Input.isKeyPressed(Input.KEY_A) then
        camera:slide(-1)
    end
    if Input.isKeyPressed(Input.KEY_D) then
        camera:slide(1)
    end
end

function onTouchStart(pointer, x, y)
    lastX = x
    lastY = y
    lastPressX = x
    lastPressY = y
end

function onTouchMove(pointer, x, y)
    difX = lastX - x
    lastX = x
    camera:rotateView(0.1 * difX)

    difY = lastY - y
    lastY = y
    camera:elevateView(-0.1 * difY)
end

function onKeyDown(key, rep, mods)
    if (key == Input.KEY_X) then
        camera:setPosition(camera.position.x, camera.position.y+10, camera.position.z);
        camera:setView(camera.view.x, camera.view.y+10, camera.view.z);
    end

    if (key == Input.KEY_Z) then
        camera:setPosition(camera.position.x, camera.position.y-10, camera.position.z);
        camera:setView(camera.view.x, camera.view.y-10, camera.view.z);
    end
end

function onKeyUp(key, rep, mods)
    if (key == Input.KEY_F) then
        if (not System.isFullscreen()) then
            System.requestFullscreen();
        else
            System.exitFullscreen();
        end
    end
end


camera.position = Vector3(0, 15, -60)

terrain.name = "terrain"

terrain:setHeightMap("heightmap.png")
terrain:setTexture("ground.png")
terrain:setBlendMap("blendmap.png")

terrain:setTextureDetailRed("block.png");
terrain:setTextureDetailGreen("block.png");
terrain:setTextureDetailBlue("block.png");

scene.camera = camera.entity;

scene.ambientLightFactor = 0.2;

sun:setType(LightType.DIRECTIONAL)
sun:setDirection(0.0, -0.3, -0.8)
sun:setShadows(true)

text.text = "Texto";
text:setPosition(100, 100, 0);
text2:setPosition(100, 150, 0);
text3:setPosition(100, 200, 0);
text4:setPosition(100, 250, 0);

Engine.setCanvasSize(1000,480)
Engine.setScene(scene)
Engine.addSceneLayer(uiscene)
Engine.callTouchInMouseEvent = true

Engine.onUpdate = onUpdate
Engine.onTouchStart = onTouchStart
Engine.onTouchMove = onTouchMove
Engine.onKeyDown = onKeyDown
Engine.onKeyUp = onKeyUp

--Lua file
Engine.setCanvasSize(1000,480)

cena = Scene();

plano = PlaneTerrain(500, 500);
plano:setTexture('ground.png');
--plano:setColor(0.6, 0.0, 0.6, 1)
plano:setPosition(0,0,0);
cena:addObject(plano);

cubo = Cube(10,10,10);
--cubo:setColor(0.6, 0.6, 0.0, 1)
cubo:setPosition(250,0,250);
cubo:setTexture('block.png');
--cena:addObject(cubo);

som = Sound("teste.wav")

Engine.setScene(cena);

luz = DirectionalLight();
luz:setDirection(-8,-10,4);
luz:setShadow(true);
cena:addObject(luz);

luz2 = PointLight();
luz2:setPosition(250,100,250);
luz2:setPower(200);
--cena:addObject(luz2);

luz3 = PointLight();
luz3:setPosition(250,100,0);
luz3:setPower(200);
--cena:addObject(luz3);

sky = SkyBox();
sky:setTextureFront("ely_hills/hills_lf.tga");
sky:setTextureBack("ely_hills/hills_rt.tga");
sky:setTextureLeft("ely_hills/hills_bk.tga");
sky:setTextureRight("ely_hills/hills_ft.tga");
sky:setTextureUp("ely_hills/hills_up.tga");
sky:setTextureDown("ely_hills/hills_dn.tga");
cena:addObject(sky)

cena:setAmbientLight(0.1);

camera = Camera();
camera:setPosition(250, 60, 400)
camera:setView(250,0, 250);
cena:setCamera(camera);
--camera:rotatePosition(0.001);

local walkForward = false
local walkBack = false
local turnLeft = false
local turnRight = false
local slideLeft = false
local slideRight = false
local upCamera = false
local downCamera = false

function onUpdate()
    if (walkForward) then
        camera:walkForward(1)
    end
    if (walkBack) then
        camera:walkForward(-1)
    end
    if (turnLeft) then
        camera:rotateView(1)
    end
    if (turnRight) then
        camera:rotateView(-1)
    end
    if (slideLeft) then
        camera:slide(-1)
    end
    if (slideRight) then
        camera:slide(1)
    end
    if (upCamera) then
        camera:setPosition(camera:getPosition().x, camera:getPosition().y+1, camera:getPosition().z)
        camera:setView(camera:getView().x, camera:getView().y+1, camera:getView().z)
    end
    if (downCamera) then
        camera:setPosition(camera:getPosition().x, camera:getPosition().y-1, camera:getPosition().z)
        camera:setView(camera:getView().x, camera:getView().y-1, camera:getView().z)
    end
end
Engine.onUpdate = onUpdate;

local elementos = {}
local maxY = 0;

local ultimoX;
local ultimoY;
local ultimoPressX;
local ultimoPressY;
local cameraY = camera:getPosition().y
local cameraZ = camera:getPosition().z

function hasCube(x, y, z)
    local count = 0
    for k,v in pairs(elementos) do
        if ((v.cubo:getPosition().x == x)and (v.cubo:getPosition().y == y) and (v.cubo:getPosition().z == z)) then
            return true
        end
    end
    return false
end

function destroyCube(x, y, z)
    local count = 0
    for k,v in pairs(elementos) do
        if ((v.cubo:getPosition().x == x)and (v.cubo:getPosition().y == y) and (v.cubo:getPosition().z == z)) then
            v.cubo:destroy();
            table.remove(elementos, k)
        end
    end
end

function distanceVectors(vector1, vector2)
    local xd = vector2.x - vector1.x
    local yd = vector2.y - vector1.y
    local zd = vector2.z - vector1.z
    return math.sqrt(xd*xd + yd*yd + zd*zd)
end

function addOrRemoveCube(add, x, y)
    if ((math.abs(ultimoPressX-x) < 10) and (math.abs(ultimoPressY-y) < 10)) then
        ray = camera:pointsToRay(x, y);

        local mdistance = 10000000
        local mclick
        local mclickremove
        for i = 0,(maxY+10),10 do
            local click = ray:intersectionPointPlane(Plane(Vector3(0, 1, 0), Vector3(0, i, 0)))
            if (i > 0) then
                local positionX = math.floor(click.x/10) * 10
                local positionY = math.floor(click.y/10) * 10
                local positionZ = math.floor(click.z/10) * 10
                if (hasCube(positionX,i-10,positionZ)) then
                    local dis = distanceVectors(camera:getPosition(), click)
                    if (dis < mdistance) then
                        mdistance = dis
                        mclick = Vector3(positionX,positionY,positionZ)
                        mclickremove = Vector3(positionX,i-10,positionZ)
                    end
                end
                if (hasCube(positionX,i,positionZ)) then
                    local dis = distanceVectors(camera:getPosition(), click)
                    if (dis < mdistance) then
                        mdistance = dis
                        mclick = Vector3(positionX,positionY-10,positionZ)
                        mclickremove = Vector3(positionX,i,positionZ)
                    end
                end
            else
                mclick = click
            end
        end

        for i = 0,500,10 do
            local click = ray:intersectionPointPlane(Plane(Vector3(1, 0, 0), Vector3(i, 0, 0)))
            local positionX = math.floor(click.x/10) * 10
            local positionY = math.floor(click.y/10) * 10
            local positionZ = math.floor(click.z/10) * 10
            if (hasCube(positionX-10,positionY,positionZ)) then
                local dis = distanceVectors(camera:getPosition(), click)
                if (dis < mdistance) then
                    mdistance = dis
                    mclick = Vector3(positionX,positionY,positionZ)
                    mclickremove = Vector3(positionX-10,positionY,positionZ)
                end
            end
            if (hasCube(positionX,positionY,positionZ)) then
                local dis = distanceVectors(camera:getPosition(), click)
                if (dis < mdistance) then
                    mdistance = dis
                    mclick = Vector3(positionX-10,positionY,positionZ)
                    mclickremove = Vector3(positionX,positionY,positionZ)
                end
            end
        end

        for i = 0,500,10 do
            local click = ray:intersectionPointPlane(Plane(Vector3(0, 0, 1), Vector3(0, 0, i)))
            local positionX = math.floor(click.x/10) * 10
            local positionY = math.floor(click.y/10) * 10
            local positionZ = math.floor(click.z/10) * 10
            if (hasCube(positionX,positionY,positionZ-10)) then
                local dis = distanceVectors(camera:getPosition(), click)
                if (dis < mdistance) then
                    mdistance = dis
                    mclick = Vector3(positionX,positionY,positionZ)
                    mclickremove = Vector3(positionX,positionY,positionZ-10)
                end
            end
            if (hasCube(positionX,positionY,positionZ)) then
                local dis = distanceVectors(camera:getPosition(), click)
                if (dis < mdistance) then
                    mdistance = dis
                    mclick = Vector3(positionX,positionY,positionZ-10)
                    mclickremove = Vector3(positionX,positionY,positionZ)
                end
            end
        end

        if (add) then
            local positionX = math.floor(mclick.x/10) * 10
            local positionY = math.floor(mclick.y);
            local positionZ = math.floor(mclick.z/10) * 10
            if ( positionY < 0) then positionY = 0 end

            if (not hasCube(positionX,positionY,positionZ)) then
                if (positionY > maxY) then maxY = positionY end
                novocubo = {}
                novocubo.cubo = Cube(10,10,10);
                novocubo.cubo:setTexture('block.png');
                novocubo.cubo:setPosition(positionX , positionY ,positionZ)
                table.insert(elementos,novocubo)
                --som:play()
                print('cubo', positionX, positionY, positionZ)
                cena:addObject(novocubo.cubo);
                --novocubo.cubo:addObject(imagem);
            end
        end

        if ((not add)) then
            if not (mclickremove == nil) then
                local positionX = math.floor(mclickremove.x/10) * 10
                local positionY = math.floor(mclickremove.y);
                local positionZ = math.floor(mclickremove.z/10) * 10
                print('removido cubo', positionX, positionY, positionZ)
                destroyCube(positionX, positionY, positionZ)
            end
        end

    end
end

function onTouchStart(pointer, x, y)
    ultimoX = x
    ultimoY = y
    ultimoPressX = x
    ultimoPressY = y
end
Engine.onTouchStart = onTouchStart;

function onTouchEnd(pointer, x, y)
    addOrRemoveCube(true, x, y)
end
Engine.onTouchEnd = onTouchEnd;

function onTouchDrag(pointer, x, y)
    difX = ultimoX - x
    ultimoX = x
    camera:rotateView(0.1 * difX)

    difY = ultimoY - y
    ultimoY = y
    camera:elevateView(-0.1 * difY)
    --camera:moveForward(0.5 * difY)
    --camera:elevateView(-0.001 * difY)
    --camera:moveForward(0.1 * difY)
    --camera:walkForward(0.1* difY);
    --camera:slide(0.1* difY);
end
Engine.onTouchDrag = onTouchDrag;

function onKeyDown(key)
    if ((key == Input.KEY_UP) or (key==Input.KEY_W)) then
        walkForward = true
    end
    if ((key == Input.KEY_DOWN) or (key==Input.KEY_S)) then
        walkBack = true
    end
    if (key == Input.KEY_LEFT) then
        turnLeft = true
    end
    if (key == Input.KEY_RIGHT) then
        turnRight = true
    end
    if (key == Input.KEY_A) then
        slideLeft = true
    end
    if (key == Input.KEY_D) then
        slideRight = true
    end
    if (key == Input.KEY_Z) then
        upCamera = true
    end
    if (key == Input.KEY_X) then
        downCamera = true
    end
end
Engine.onKeyDown = onKeyDown;

function onKeyUp(key)
    if ((key == Input.KEY_UP) or (key==Input.KEY_W)) then
        walkForward = false
    end
    if ((key == Input.KEY_DOWN) or (key==Input.KEY_S)) then
        walkBack = false
    end
    if (key == Input.KEY_LEFT) then
        turnLeft = false
    end
    if (key == Input.KEY_RIGHT) then
        turnRight = false
    end
    if (key == Input.KEY_A) then
        slideLeft = false
    end
    if (key == Input.KEY_D) then
        slideRight = false
    end
    if (key == Input.KEY_Z) then
        upCamera = false
    end
    if (key == Input.KEY_X) then
        downCamera = false
    end
end
Engine.onKeyUp = onKeyUp;

function onMouseDown(button, x, y)
    onTouchStart(button,x,y)
end
Engine.onMouseDown = onMouseDown;

function onMouseUp(button, x, y)
    if (button == Input.MOUSE_BUTTON_LEFT) then
        onTouchEnd(button,x,y)
    end
    if (button == Input.MOUSE_BUTTON_RIGHT) then
        addOrRemoveCube(false, x, y)
    end
end
Engine.onMouseUp = onMouseUp;

function onMouseDrag(button, x, y)
    onTouchDrag(button, x,y)
end
Engine.onMouseDrag = onMouseDrag;

function onMouseMove(x, y)
    --print("mouse move", x, y)
end
Engine.onMouseMove = onMouseMove;

function onTextInput(text)
    --print(text)
end
Engine.onTextInput = onTextInput;
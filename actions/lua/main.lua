scene = Scene()

text = Text(scene)

polygon = MeshPolygon(scene)
polygon2 = MeshPolygon(scene)
polygon3 = Polygon(scene)
polygon4 = Polygon(scene)

positionaction = PositionAction(scene)
rotationaction = RotationAction(scene)
scaleaction = ScaleAction(scene)
coloraction = ColorAction(scene)
alphaaction = AlphaAction(scene)
timedaction = TimedAction(scene)


function onActionStep()
    angle = math.pi * 2.0 * timedaction:getValue()
    polygon4:setPosition(math.cos(angle)*100 + 450, math.sin(angle)*100 + 300, 0);
end

function onActionStart()
    Log.verbose("Rotation action start")
end

function onTouchStart(pointer, x, y)
    positionaction:start()
    rotationaction:start()
    scaleaction:start()
    coloraction:start()
    alphaaction:start()
    timedaction:start()
end


text.text = "Click on screen to start"
text.anchorPreset = AnchorPreset.CENTER_TOP

polygon:addVertex(0, 0);
polygon:addVertex(100, 0);
polygon:addVertex(0, 100);
polygon:addVertex(100, 100);
polygon:setColor(1.0, 0.3, 0.8, 1.0);
polygon:setPosition(50, 50, 0);
polygon.name = "Polygon1";

polygon2:addVertex(0, 0)
polygon2:addVertex(100, 0)
polygon2:addVertex(0, 100)
polygon2:addVertex(100, 100)
polygon2:setColor(1.0, 0.5, 1.0, 1.0)
polygon2:setPosition(450, 50, 0)
polygon2.name = "Polygon2"

polygon3:addVertex(0, 0)
polygon3:addVertex(100, 0)
polygon3:addVertex(0, 100)
polygon3:addVertex(100, 100)
polygon3:setColor(0.5, 1.0, 1.0, 1.0)
polygon3:setPosition(800, 50, 0)
polygon3.name = "Polygon3"

polygon4:addVertex(0, 0)
polygon4:addVertex(100, 0)
polygon4:addVertex(0, 100)
polygon4:addVertex(100, 100)
polygon4:setColor(0.5, 1.0, 0.3, 1.0)
polygon4:setPosition(450, 300, 0)
polygon4.name = "Polygon4"

polygon2:moveToTop();

startRot = Quaternion()
endRot = Quaternion()
startRot:fromAngle(Angle.degToDefault(0))
endRot:fromAngle(Angle.degToDefault(180))
rotationaction:setAction(startRot, endRot, 5, false)
rotationaction.target = polygon3.entity
rotationaction:getActionComponent().onStart = onActionStart

scaleaction:setAction(Vector3(1,1,1), Vector3(2,2,2), 10, false)
scaleaction.target = polygon2.entity

coloraction:setAction(polygon.color, Vector4(0.0, 0.0, 1.0, 1.0), 5, false)
coloraction.target = polygon.entity

alphaaction:setAction(1.0, 0.3, 5, false)
alphaaction.target = polygon2.entity

positionaction:setAction(Vector3(20,20,0), Vector3(200,200,0), 5, true)
positionaction.target = polygon.entity
positionaction:setFunctionType(EaseType.ELASTIC_IN_OUT)
positionaction.speed = 1

timedaction.duration = 10
timedaction:getActionComponent().onStep = onActionStep;

Engine.setScene(scene)
Engine.setCallTouchInMouseEvent(true)

Engine.onTouchStart = onTouchStart
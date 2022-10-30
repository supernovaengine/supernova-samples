scene = Scene()

polygon = MeshPolygon(scene)
polygon2 = MeshPolygon(scene)
polygon3 = Polygon(scene)
positionaction = PositionAction(scene)
rotationaction = RotationAction(scene)
scaleaction = ScaleAction(scene)
coloraction = ColorAction(scene)
alphaaction = AlphaAction(scene)


function onActionStart()
    Log.verbose("Action start")
end

function onTouchStart(pointer, x, y)
    positionaction:start()
    rotationaction:start()
    scaleaction:start()
    coloraction:start()
    alphaaction:start()
end

polygon:addVertex(0, 0);
polygon:addVertex(200, 0);
polygon:addVertex(0, 200);
polygon:addVertex(200, 200);
polygon:setColor(1.0, 0.3, 0.8, 1.0);
polygon:setPosition(50, 50, 0);
polygon.name = "Polygon1";

polygon2:addVertex(0, 0)
polygon2:addVertex(200, 0)
polygon2:addVertex(0, 200)
polygon2:addVertex(200, 200)
polygon2:setColor(1.0, 0.5, 1.0, 1.0)
polygon2:setPosition(350, 50, 0)
polygon.name = "Polygon2"

polygon3:addVertex(0, 0)
polygon3:addVertex(200, 0)
polygon3:addVertex(0, 200)
polygon3:addVertex(200, 200)
polygon3:setColor(0.5, 1.0, 1.0, 1.0)
polygon3:setPosition(650, 50, 0)
polygon.name = "Polygon3"

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

Engine.setScene(scene)
Engine.setCallTouchInMouseEvent(true)

Engine.onTouchStart = onTouchStart
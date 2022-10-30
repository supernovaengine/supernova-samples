scene = Scene()

sprite = Sprite(scene)
sprite2 = Sprite(scene)
spriteanim = SpriteAnimation(scene)


function onActionStart()
    Log.verbose("Sprite start");
end

function onTouchStart(pointer, x, y)
    spriteanim:start()
    sprite2:startAnimation(0, 7, 200, true)
end


sprite:setTexture("dino.png")
for i=0,7 do
    sprite:addFrame(i, "", Rect((i+1.0)/8, 0.0, 1.0/8, 1.0))
end
sprite:setFrame(0)
sprite.name = "Sprite"
sprite:setPosition(20,20,0)
sprite:setSize(200,200)

spriteanim.target = sprite.entity
spriteanim:setAnimation(0, 7, 100, true)
spriteanim:getActionComponent().onStart = onActionStart

sprite2:setTexture("dino.png")
for i=0,7 do
    sprite2:addFrame(i, "", Rect((i+1.0)/8, 0.0, 1.0/8, 1.0))
end
sprite2:setFrame(0)
sprite2.name = "Sprite2"
sprite2:setPosition(400,20,0)
sprite2:setSize(200,200)

Engine.setScene(scene);
Engine.setCallTouchInMouseEvent(true);

Engine.onTouchStart = onTouchStart
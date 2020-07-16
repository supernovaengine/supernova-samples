Engine.setCanvasSize(1000,480)

cena = Scene()
triangulo = Polygon()

triangulo:addVertex(0, -100, 0)
triangulo:addVertex(-50, 50, 0)
triangulo:addVertex(50, 50, 0)

triangulo:setPosition(300,300,0)
triangulo:setColor(0.6, 0.2, 0.6, 1)

cena:addObject(triangulo)

Engine.setScene(cena)
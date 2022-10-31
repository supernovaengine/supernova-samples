scene = Scene()

button_save = Button(scene)
button_read = Button(scene)
button_storage_save = Button(scene)
button_storage_read = Button(scene)


function onButton_save()
    Log.verbose("Save file path: " .. FileData.getSystemPath("data://test.txt"))
    file = File("data://test.txt", true)
    file:writeString("The string has words and keyword\n")
    file:writeString("This is a string which is written to a file\n")
    file:flush()
end

function onButton_read()
    Log.verbose("Read file path: " .. FileData.getSystemPath("data://test.txt"))
    file = File()
    if (file:open("data://test.txt") == FileErrors.FILEDATA_OK) then
        Log.verbose(file:readString(file:length()))
    end
end

function onButton_storage_save()
    Log.verbose("Save key-value");

    UserSettings.setBoolForKey("key1", true)
    UserSettings.setIntegerForKey("key2", 55)
    UserSettings.setLongForKey("key3", 5454545454545454545)
    UserSettings.setFloatForKey("key4", 23.54)
    UserSettings.setDoubleForKey("key5", 23434.645454)
    UserSettings.setStringForKey("key6", "testing string")
    data = Data("data://test.txt")
    UserSettings.setDataForKey("key7", data)
end

function onButton_storage_read()
    boolStr = "false"
    if (UserSettings.getBoolForKey("key1")) then
        boolStr = "true"
    end
    Log.verbose("Read bool key-value: " .. boolStr)
    Log.verbose("Read integer key-value: " .. UserSettings.getIntegerForKey("key2"))
    Log.verbose("Read long key-value: " .. UserSettings.getLongForKey("key3"))
    Log.verbose("Read float key-value: " .. UserSettings.getFloatForKey("key4"))
    Log.verbose("Read double key-value: " .. UserSettings.getDoubleForKey("key5"))
    Log.verbose("Read string key-value: " .. UserSettings.getStringForKey("key6"))

    data = UserSettings.getDataForKey("key7");
    Log.verbose("Read data key-value: " .. data:readString())

    Log.verbose("Deleting key4")
    UserSettings.removeKey("key4")
end


button_save:setTexture("asset://Button_Normal.png")
button_save:setTexturePressed("/Button_Disable.png")
button_save:setPosition(100, 100, 0)
button_save:setSize(200, 100)
button_save:setMargin(5)
button_save.label = "Save"
button_save.fontSize = 40
button_save.labelColor = Vector4(0.2, 0.2, 0.2, 1.0)
button_save:getButtonComponent().onRelease = onButton_save;

button_read:setTexture("Button_Normal.png")
button_read:setTexturePressed("Button_Disable.png")
button_read:setPosition(500, 100, 0)
button_read:setSize(200, 100)
button_read:setMargin(5)
button_read.label = "Read"
button_read.fontSize = 40
button_read.labelColor = Vector4(0.2, 0.2, 0.2, 1.0)
button_read:getButtonComponent().onRelease = onButton_read

button_storage_save:setTexture("Button_Normal.png")
button_storage_save:setTexturePressed("Button_Disable.png")
button_storage_save:setPosition(100, 300, 0)
button_storage_save:setSize(300, 100)
button_storage_save:setMargin(5)
button_storage_save.label = "Save user setting"
button_storage_save.fontSize = 40
button_storage_save.labelColor = Vector4(0.2, 0.2, 0.2, 1.0)
button_storage_save:getButtonComponent().onRelease = onButton_storage_save

button_storage_read:setTexture("Button_Normal.png")
button_storage_read:setTexturePressed("Button_Disable.png")
button_storage_read:setPosition(500, 300, 0)
button_storage_read:setSize(300, 100)
button_storage_read:setMargin(5)
button_storage_read.label = "Read user setting"
button_storage_read.fontSize = 40
button_storage_read.labelColor = Vector4(0.2, 0.2, 0.2, 1.0)
button_storage_read:getButtonComponent().onRelease = onButton_storage_read

Engine.setCanvasSize(1000,480)
Engine.setScene(scene)
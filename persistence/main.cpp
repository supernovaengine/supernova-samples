#include "Supernova.h"

#include "Scene.h"
#include "Polygon.h"
#include "File.h"
#include "System.h"
#include "Log.h"
#include "Button.h"
#include "UserSettings.h"

using namespace Supernova;
Button button_save;
Button button_read;
Button button_storage_save;
Button button_storage_read;
Scene cena;

void onPress_save(){
    Log::Verbose("Save file path: %s", FileData::getSystemPath("data://teste.txt").c_str());
    File* file = new File("data://teste.txt", true);
    file->writeString("The string has words and keyword\n");
    file->writeString("This is a string which is written to a file\n");
    delete file;
}

void onPress_read(){
    Log::Verbose("Read file path: %s", FileData::getSystemPath("data://teste.txt").c_str());
    File* file = new File();
    if (file->open("data://teste.txt")==FileErrors::NO_ERROR) {
        Log::Verbose("%s", file->readString().c_str());
    }
    delete file;
}

void onPress_storage_save(){
    Log::Verbose("Save key-value");

    UserSettings::setBoolForKey("key1", true);
    UserSettings::setIntegerForKey("key2", 55);
    UserSettings::setLongForKey("key3", (long)5454545454545454545);
    UserSettings::setFloatForKey("key4", 23.54f);
    UserSettings::setDoubleForKey("key5", 23434.645454);
    UserSettings::setStringForKey("key6", "testing string");
    Data data("data://teste.txt");
    UserSettings::setDataForKey("key7", data);
}

void onPress_storage_read(){
    std::string boolStr = "false";
    if (UserSettings::getBoolForKey("key1")) {
        boolStr = "true";
    }
    Log::Verbose("Read bool key-value: %s", boolStr.c_str());
    Log::Verbose("Read integer key-value: %i", UserSettings::getIntegerForKey("key2"));
    Log::Verbose("Read long key-value: %ld", UserSettings::getLongForKey("key3"));
    Log::Verbose("Read float key-value: %f", UserSettings::getFloatForKey("key4"));
    Log::Verbose("Read double key-value: %f", UserSettings::getDoubleForKey("key5"));
    Log::Verbose("Read string key-value: %s", UserSettings::getStringForKey("key6").c_str());

    Data data = UserSettings::getDataForKey("key7");
    Log::Verbose("Read data key-value: %s", data.readString().c_str());

    Log::Verbose("Deleting key4");
    UserSettings::removeKey("key4");
}

void init(){
    Engine::setCanvasSize(1000,480);

    button_save.setTexture("asset://Button_Normal.png");
    button_save.setTexturePressed("/Button_Disable.png");
    button_save.setPosition(100, 100, 0);
    button_save.setSize(200, 100);
    button_save.setBorder(16);
    button_save.setLabelText("Save");
    button_save.setLabelSize(40);
    button_save.setLabelColor(Vector4(0.2, 0.2, 0.2, 1.0));
    button_save.onUp = onPress_save;
    cena.addObject(&button_save);

    button_read.setTexture("Button_Normal.png");
    button_read.setTexturePressed("Button_Disable.png");
    button_read.setPosition(400, 100, 0);
    button_read.setSize(200, 100);
    button_read.setBorder(16);
    button_read.setLabelText("Read");
    button_read.setLabelSize(40);
    button_read.setLabelColor(Vector4(0.2, 0.2, 0.2, 1.0));
    button_read.onUp = onPress_read;
    cena.addObject(&button_read);

    button_storage_save.setTexture("Button_Normal.png");
    button_storage_save.setTexturePressed("Button_Disable.png");
    button_storage_save.setPosition(100, 300, 0);
    button_storage_save.setSize(250, 100);
    button_storage_save.setBorder(16);
    button_storage_save.setLabelText("Save storage");
    button_storage_save.setLabelSize(40);
    button_storage_save.setLabelColor(Vector4(0.2, 0.2, 0.2, 1.0));
    button_storage_save.onUp = onPress_storage_save;
    cena.addObject(&button_storage_save);

    button_storage_read.setTexture("Button_Normal.png");
    button_storage_read.setTexturePressed("Button_Disable.png");
    button_storage_read.setPosition(400, 300, 0);
    button_storage_read.setSize(250, 100);
    button_storage_read.setBorder(16);
    button_storage_read.setLabelText("Read storage");
    button_storage_read.setLabelSize(40);
    button_storage_read.setLabelColor(Vector4(0.2, 0.2, 0.2, 1.0));
    button_storage_read.onUp = onPress_storage_read;
    cena.addObject(&button_storage_read);

    Engine::setScene(&cena);
}
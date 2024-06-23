#include "Supernova.h"
using namespace Supernova;

Scene scene;

Button button_save(&scene);
Button button_read(&scene);
Button button_storage_save(&scene);
Button button_storage_read(&scene);


void onButton_save(){
    Log::verbose("Save file path: %s", FileData::getSystemPath("data://test.txt").c_str());
    File* file = new File("data://test.txt", true);
    file->writeString("The string has words and keyword\n");
    file->writeString("This is a string which is written to a file\n");
    delete file;
}

void onButton_read(){
    Log::verbose("Read file path: %s", FileData::getSystemPath("data://test.txt").c_str());
    File* file = new File();
    if (file->open("data://test.txt")==FileErrors::FILEDATA_OK) {
        Log::verbose("%s", file->readString().c_str());
    }
    delete file;
}

void onButton_storage_save(){
    Log::verbose("Save key-value");

    UserSettings::setBoolForKey("key1", true);
    UserSettings::setIntegerForKey("key2", 55);
    UserSettings::setLongForKey("key3", (long)5454545454545454545);
    UserSettings::setFloatForKey("key4", 23.54f);
    UserSettings::setDoubleForKey("key5", 23434.645454);
    UserSettings::setStringForKey("key6", "testing string");
    Data data("data://test.txt");
    UserSettings::setDataForKey("key7", data);
}

void onButton_storage_read(){
    std::string boolStr = "false";
    if (UserSettings::getBoolForKey("key1")) {
        boolStr = "true";
    }
    Log::verbose("Read bool key-value: %s", boolStr.c_str());
    Log::verbose("Read integer key-value: %i", UserSettings::getIntegerForKey("key2"));
    Log::verbose("Read long key-value: %ld", UserSettings::getLongForKey("key3"));
    Log::verbose("Read float key-value: %f", UserSettings::getFloatForKey("key4"));
    Log::verbose("Read double key-value: %f", UserSettings::getDoubleForKey("key5"));
    Log::verbose("Read string key-value: %s", UserSettings::getStringForKey("key6").c_str());

    Data data = UserSettings::getDataForKey("key7");
    Log::verbose("Read data key-value: %s", data.readString().c_str());

    Log::verbose("Deleting key4");
    UserSettings::removeKey("key4");
}

void init(){
    button_save.setTexture("asset://Button_Normal.png");
    button_save.setTexturePressed("/Button_Disable.png");
    button_save.setPosition(100, 100, 0);
    button_save.setSize(200, 100);
    button_save.setPatchMargin(5);
    button_save.setLabel("Save");
    button_save.setLabelFontSize(40);
    button_save.setLabelColor(Vector4(0.2, 0.2, 0.2, 1.0));
    button_save.getComponent<ButtonComponent>().onRelease = onButton_save;

    button_read.setTexture("Button_Normal.png");
    button_read.setTexturePressed("Button_Disable.png");
    button_read.setPosition(500, 100, 0);
    button_read.setSize(200, 100);
    button_read.setPatchMargin(5);
    button_read.setLabel("Read");
    button_read.setLabelFontSize(40);
    button_read.setLabelColor(Vector4(0.2, 0.2, 0.2, 1.0));
    button_read.getComponent<ButtonComponent>().onRelease = onButton_read;

    button_storage_save.setTexture("Button_Normal.png");
    button_storage_save.setTexturePressed("Button_Disable.png");
    button_storage_save.setPosition(100, 300, 0);
    button_storage_save.setSize(300, 100);
    button_storage_save.setPatchMargin(5);
    button_storage_save.setLabel("Save user setting");
    button_storage_save.setLabelFontSize(40);
    button_storage_save.setLabelColor(Vector4(0.2, 0.2, 0.2, 1.0));
    button_storage_save.getComponent<ButtonComponent>().onRelease = onButton_storage_save;

    button_storage_read.setTexture("Button_Normal.png");
    button_storage_read.setTexturePressed("Button_Disable.png");
    button_storage_read.setPosition(500, 300, 0);
    button_storage_read.setSize(300, 100);
    button_storage_read.setPatchMargin(5);
    button_storage_read.setLabel("Read user setting");
    button_storage_read.setLabelFontSize(40);
    button_storage_read.setLabelColor(Vector4(0.2, 0.2, 0.2, 1.0));
    button_storage_read.getComponent<ButtonComponent>().onRelease = onButton_storage_read;

    Engine::setCanvasSize(1000,480);
    Engine::setScene(&scene);
}
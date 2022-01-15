#include "headers/schemerlamp.h"

#include <utility>

schemerlamp::schemerlamp(int id, string name, const string& path): statefile(path), log("log.txt"), lamp(false) {
    this->id = id;
    this->name = std::move(name);
    this->path = path;
}

bool schemerlamp::zetLed(bool state) {
    if (state) {
        statefile.modifyFileLine(name, name + " 1");
        log.appendLine(name + " is aan");
        return true;
    }
    else {
        statefile.modifyFileLine(name, name + " 0");
        log.appendLine(name + " is uit");
        return false;
    }
}

bool schemerlamp::toggleLed(){
    if (lamp){
        zetLed(false);
        lamp = false;
        return true;
    }
    else{
        zetLed(true);
        lamp = true;
        return false;
    }
}
#include "headers/bed.h"

#include <utility>

bed::bed(int id, string name, const string& path): statefile(path), log("log.txt"), bedSwitch(false) {
    this->id = id;
    this->name = std::move(name);
    this->path = path;
}

bool bed::zetLed(bool state){
    if (state){
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

bool bed::toggleLed(){
    if (bedSwitch){
        zetLed(false);
        bedSwitch = false;
        return true;
    }
    else{
        zetLed(true);
        bedSwitch = true;
        return false;
    }
}
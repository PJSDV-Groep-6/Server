#include "headers/schemerlamp.h"

#include <utility>

schemerlamp::schemerlamp(int id, string name, const string& path): statefile(path), log("log.txt"), lamp(false) {
    this->id = id;
    this->name = std::move(name);
    this->path = path;
}

bool schemerlamp::zetLed(bool state) {
    if (state) {
        statefile.modify_file_line(name, name + " 1");
        log.append_line(name + " is aan");
        return true;
    }
    else {
        statefile.modify_file_line(name, name + " 0");
        log.append_line(name + " is uit");
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
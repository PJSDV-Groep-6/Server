#include "headers/bed.h"

#include <utility>

bed::bed(int given_id, string given_name, const string& given_path):  meubel(given_id, given_name, given_path), statefile(given_path), id(given_id), name (given_name), path(given_path), log("log.txt"), bedSwitch(false) {
    // this->id = id;
    // this->name = std::move(name);
    // this->path = path;
}

bool bed::zetLed(bool state){
    if (state){
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
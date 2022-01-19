#include "headers/muur.h"

muur::muur(int id, string name, const string& path): meubel(id, name, path) , statefile(path), log("log.txt") {

}

bool muur::input(int id, string message){
    if (id == this->id){
        if (message == "donker" && !mem){
            zetState(true);
            return true;
        }
        else if (message == "licht" && mem) {
            zetState(false);
        }
    }
    return false;
}

bool muur::zetState(bool state){
    checkBrand();
    if (state || brand){
        statefile.modifyFileLine(name, name + " 1");
        log.appendLine(name + " is aan");
        this->mem = true;
        return true;
    }
    else if (!brand && !state){
        statefile.modifyFileLine(name, name + " 0");
        log.appendLine(name + " is uit");
        this->mem = false;
        return false;
    }
    return mem;
}
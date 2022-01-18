#include "headers/meubel.h"
#include <cstring>

meubel::meubel(int gegeven_id, string gegeven_name, string gegeven_path): name(gegeven_name), path(gegeven_path), id(gegeven_id), statefile(gegeven_path), log("log.txt") {
    if(statefile.gotoLine(gegeven_name) == -1) {
        statefile.appendLine(gegeven_name + " 0 0");
    }
}

bool meubel::zetLed(bool state){
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

bool meubel::toggleLed(){
    if (led){
        zetLed(false);
        led = false;
        return true;
    }
    else{
        zetLed(true);
        led = true;
        return false;
    }
}
#include "headers/meubel.h"

meubel::meubel(int gegeven_id, string gegeven_name, string gegeven_path): name(gegeven_name), path(gegeven_path), id(gegeven_id), statefile(gegeven_path), log("log.txt") {

}

bool meubel::zetLed(bool state){
    if (state){
        statefile.modifyFileLine(name, name + " 1");
        log.append_line(name + " is aan");
        return true;
    }
    else {
        statefile.modifyFileLine(name, name + " 0");
        log.append_line(name + " is uit");
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

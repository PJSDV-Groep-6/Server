#include "headers/meubel.h"

meubel::meubel(int gegeven_id, string gegeven_name, string gegeven_path): name(gegeven_name), path(gegeven_path), id(gegeven_id), statefile(gegeven_path), log("log.txt") {

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

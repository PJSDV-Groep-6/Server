#include "headers/meubel.h"

meubel::meubel(int gegeven_id, string gegeven_name, string gegeven_path): name(gegeven_name), path(gegeven_path), id(gegeven_id), statefile(gegeven_path), log("log.txt") {

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

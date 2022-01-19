#include "headers/schemerlamp.h"

#include <utility>

schemerlamp::schemerlamp(int id, string name, const string& path): meubel(id, name, path) , statefile(path), log("log.txt"), lamp(false) {
    
}

bool schemerlamp::input(int id, string message){
    if (id == this->id){
        if (message == "Beweging" && !mem){
            zetState(true);
            return true;
        }
        else if (message == "Beweging" && mem) {
            zetState(false);
            return false;
        }
    } else return false;
}

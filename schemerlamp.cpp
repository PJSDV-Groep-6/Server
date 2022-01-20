#include "headers/schemerlamp.h"

schemerlamp::schemerlamp(int id, string name, const string& path, string internal): meubel(id, name, path, internal) , statefile(path), log("log.txt"), lamp(false), istates(internal) {
    if(istates.gotoLine(name + "bewegingssensor") == -1) {
        istates.appendLine(name + "bewegingssensor 0");
        state = name + "bewegingssensor";
    }
}

bool schemerlamp::input(int id, string message){
    if (id == this->id){
        if (message == "Beweging" || checkIState("bedLampdruksensor") == "0" && !mem){
            zetState(true);
            zetIState(state, true);
            return true;
        }
        else if (message == "Beweging" || checkIState("bedLampdruksensor") == "1" && mem) {
            zetState(false);
        }
    }
    return false;
}

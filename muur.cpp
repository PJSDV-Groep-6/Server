#include "headers/muur.h"

muur::muur(int given_id, string given_name, const string& given_path, string internal):  meubel(given_id, given_name, given_path, internal), statefile(given_path), log("log.txt"), istates(internal) {
    if(istates.gotoLine(name + "ledstrip") == -1) {
        istates.appendLine(name + "ledstrip 0");
        state1 = name + "ledstrip";
    }

    if(istates.gotoLine(name + "venster") == -1) {
        istates.appendLine(name + "venster 0");
        state2 = name + "venster";
    }
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

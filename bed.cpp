#include "headers/bed.h"
#include <iostream>
#include <utility>

bed::bed(int given_id, string given_name, const string& given_path, string internal):  meubel(given_id, given_name, given_path, internal), statefile(given_path), log("log.txt"), bedSwitch(false),
                                                                                       istates(internal) {
    if(istates.gotoLine(name + "druksensor") == -1) {
        istates.appendLine(name + "druksensor 0");
        state = name + "druksensor";
        cout << state << endl;
    }
}

bool bed::input(int id, string message){
   if (id == this->id){
       if (message == "switch"){
           return toggleState();
       }
       else if (message == "opgestaan") {
           zetState(true);
           zetIState(state, false);
           return true;
       }
       else if (message == "iemand") {
           zetIState(state, true);
       }
   } else return false;
}
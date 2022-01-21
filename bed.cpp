#include "headers/bed.h"

#include <utility>

bed::bed(int given_id, string given_name, const string& given_path, string internal):  meubel(given_id, given_name, given_path, internal), statefile(given_path), log("log.txt"), bedSwitch(false),
                                                                                       istates(internal) {
    if(istates.gotoLine(name + "druksensor") == -1) {
        istates.appendLine(name + "druksensor 0");
    }
}

bool bed::input(int id, string message){
   if (id == this->id){
       if (message == "switch"){
           return toggleState();
       }
       else if (message == "opgestaan") {
           zetState(true);
           return true;
       }
   } else return false;
}
#include "headers/deur.h"

deur::deur(int given_id, string given_name, const string& given_path, string internal):  meubel(given_id, given_name, given_path, internal), statefile(given_path), log("log.txt"),
                                                                                         istates(internal) {
    if(istates.gotoLine(name + "button") == -1) {
        istates.appendLine(name + "button 0");
    }
}

bool deur::input(int id, string message){
    if (id == this->id){
        if ((message == "insideClosed" || message == "outsideClosed") && this->state == "0"){
            zetState(true);
            return true;
        }
        else if ((message == "insideOpen" || message == "outsideOpen") && this->state == "1") {
            zetState(false);
        }
    }
    return false;
}
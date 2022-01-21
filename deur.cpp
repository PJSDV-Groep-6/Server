#include "headers/deur.h"

deur::deur(int given_id, string given_name, const string& given_path):  meubel(given_id, given_name, given_path), statefile(given_path), log("log.txt") {

}

void deur::input(int id, string message){
    if (id == this->id){
        if ((message == "insideClosed" || message == "outsideClosed") && !mem){
            zetState(true);
        }
        else if ((message == "insideOpen" || message == "outsideOpen") && mem) {
            zetState(false);
        }
    }
}
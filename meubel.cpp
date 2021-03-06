#include "headers/meubel.h"
#include <iostream>

meubel::meubel(int gegeven_id, string gegeven_name, string gegeven_path): name(gegeven_name), path(gegeven_path), id(gegeven_id), statefile(gegeven_path), log("log.txt") {
    //zorg ervoor dat er altijd een brand state wordt aangemaakt in de statefile
    if(statefile.gotoLine("brand") == -1) {
        statefile.appendLine("brand 0 1");
    }
    //zorge ervoor dat de object zijn eigen state aanmaakt in de statefile
    if(statefile.gotoLine(gegeven_name) == -1) {
        statefile.appendLine(gegeven_name + " 0 0");
    }
}

//zet de state op het meegegeven argument
bool meubel::zetState(bool state){
    checkBrand();
    if (state || brand){
        statefile.modifyFileLine(name, name + " 1");
        log.appendLine(name + " is aan");
        this->mem = true;
        return true;
    }
    else if (!brand && !state){
        statefile.modifyFileLine(name, name + " 0");
        log.appendLine(name + " is uit");
        this->mem = false;
        return false;
    }
    return mem;
}

//als de state true was zet het op false en omgekeerd
bool meubel::toggleState(){
    if (mem){
        zetState(false);
        mem = false;
        return false;
    }
    else{
        zetState(true);
        mem = true;
        return true;
    }
}

//check statefile en update eigen state naar statefile waarde
string meubel::check() {
    std::fstream file(path, std::ios::in);
    if (file.is_open()) {
        std::string line;
        std::string state;
        std::string lock;
        int value = 0;
        checkBrand();
        while (getline(file, line)) {
            std::istringstream stream(line);
            stream >> state >> value >> lock;
            if (lock == "0" && state == name && value == 1) {
                this->state = "1";
                file.close();
                return "1";
            } else if (lock == "0" && state == name && value == 0) {
                this->state = "0";
                file.close();
                return "0";
            } else if (state == name && lock == "1"){
                file.close();
                return this->state;
            }
        }
    }
    file.close();
    std::cout << this->name + " could not open " + this->path << std::endl;
}

// check als de brand state op 1 staat en zet eigen state en lock op 1
bool meubel::checkBrand() {
    std::fstream file(path, std::ios::in);
    if (file.is_open()) {
        std::string line;
        std::string state;
        std::string lock;
        int value = 0;
        while (getline(file, line)) {
            std::istringstream stream(line);
            stream >> state >> value >> lock;
            if (state == "brand" && value == 1){
                statefile.modifyFileLine(name, name + " 1 1");
                this->state = "1";
                this->brand = true;
                return true;
            }
            else if (state == "brand" && value == 0){
                this->brand = false;
                return false;
            }
        }
        return false;
    }
}
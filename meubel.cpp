#include "headers/meubel.h"
#include <iostream>

meubel::meubel(int gegeven_id, string gegeven_name, string gegeven_path, string internal): name(gegeven_name), path(gegeven_path), id(gegeven_id), statefile(gegeven_path), log("log.txt"), istatefile(internal), internal(internal) {
    if(statefile.gotoLine("brand") == -1) {
        statefile.appendLine("brand 0 1");
    }
    if(statefile.gotoLine(gegeven_name) == -1) {
        statefile.appendLine(gegeven_name + " 0 0");
    }
}

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

bool meubel::zetIState(string state,bool value){
    if (value){
        istatefile.modifyFileLine(state, state + " 1");
        //log.appendLine(name + " is aan");
        //this->mem = true;
        return true;
    }
    else if (!value){
        istatefile.modifyFileLine(state, state + " 0");
        //log.appendLine(name + " is uit");
        //this->mem = false;
        return false;
    }
    //return mem;
}

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

string meubel::checkIState(string naam) {
    std::fstream file(internal, std::ios::in);
    if (file.is_open()) {
        std::string line;
        std::string state;
        int value = 0;
        while (getline(file, line)) {
            std::istringstream stream(line);
            stream >> state >> value;
            if (state == naam && value == 1) {
                this->state = "1";
                file.close();
                return "1";
            } else if (state == naam && value == 0) {
                this->state = "0";
                file.close();
                return "0";
            } else if (state == naam && value == 2) {
                this->state = "2";
                file.close();
                return "2";
            } else if (state == naam && value == 3) {
                this->state = "3";
                file.close();
                return "3";
            }
        }
        file.close();
        std::cout << this->name + " could not open " + this->path << std::endl;
    }
}

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

int meubel::geefID() {
    return id;
}
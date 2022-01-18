#include "headers/schemerlamp.h"

#include <utility>

schemerlamp::schemerlamp(int id, string name, const string& path): meubel(id, name, path) , statefile(path), log("log.txt"), lamp(false) {
    
}

string schemerlamp::check() {
    std::fstream file(path, std::ios::in);
    if (file.is_open()) {
        std::string line;
        std::string state;
        std::string lock;
        int value = 0;
        while (getline(file, line)) {
            std::istringstream stream(line);
            stream >> state >> value >> lock;
            if (lock == "0" && state == name && value == 1) {
                this->state = "licht";
                file.close();
                return "licht";
            }
            else if(lock == "0" && state == name && value == 0){
                this->state = "thcil";
                file.close();
                return "thcil";
            }
        }
    }
    file.close();
}

void schemerlamp::aan(bool state) {
    if (state){
        statefile.modifyFileLine(name, name + "1");
    }
    else statefile.modifyFileLine(name, name + "0");
}
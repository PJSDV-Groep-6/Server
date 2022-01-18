#include "headers/deur.h"

deur::deur(int given_id, string given_name, const string& given_path):  meubel(given_id, given_name, given_path), statefile(given_path), log("log.txt") {

}

string deur::check() {
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
                this->state = "open";
                file.close();
                return "open";
            }
            else if(lock == "0" && state == name && value == 0){
                this->state = "close";
                file.close();
                return "close";
            }
        }
    }
    file.close();
}

void deur::open(bool state) {
    if (state){
        statefile.modifyFileLine(name, name + "1");
    }
    else statefile.modifyFileLine(name, name + "0");
}
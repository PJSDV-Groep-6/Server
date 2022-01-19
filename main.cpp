// Server side C/C++ program to demonstrate Socket programming
#include <string>
#include <cstring>
#include <vector>
#include "headers/socketService.h"
#include "headers/bed.h"
#include "headers/schemerlamp.h"
#include "headers/deur.h"

bool STOP(char* buffer);
void endBuffer(char* buffer, size_t length);
void clearBuffer(char* buffer, const size_t length);

int main(int argc, char const* argv[]) {
    std::vector<meubel*> meubels;
    meubels.push_back(new schemerlamp(1, "schemerLamp", "../states.cpp"));
    meubels.push_back(new deur(2, "deur", "../states.cpp"));
    meubels.push_back(new bed(3, "bedLamp", "../states.cpp"));
    const size_t bufferSize = 1024;
    char buffer[1024] = {0};
    int valread;
    int id = 0;
    std::string message;
    socketService server(8080);
    while (!STOP(buffer)) {
        server.sockAccept();
        valread = server.sockRead(buffer);
        endBuffer(buffer, valread);
        std::istringstream receive(buffer);
        receive >> id >> message;
        for(meubel* Meubel : meubels){
            Meubel->input(id, message);
            Meubel->check();
        }
        deur1.input(id, message);
        lamp1.check();
        bed1.check();
        deur1.check();
        if (message == "check") {
            switch (id) {
                case 1:
                    server.sockSend(meubels[0]->state);
                    break;
                case 2:
                    server.sockSend(meubels[1]->state);
                    break;
                case 3:
                    server.sockSend(meubels[2]->state);
                    break;
                default:
                    server.sockSend("Unkown ID");
                    break;
            }
        }
        else server.sockSend("ok");
        //clearBuffer(buffer, bufferSize);
        server.sockClose();
    }
    return 0;
}

void endBuffer(char* buffer, size_t length) {
    if (length >= 0) {
        buffer[length] = '\r';
    }
    else {
        buffer[0] = '\r';
    }
}

bool STOP(char* buffer) {
    return strncmp(buffer, "STOP", 4) == 0;
}

void clearBuffer(char* buffer, const size_t length) {
    for (int i = 0; i <= length; i++) {
        buffer[i] = 0;
    }
}
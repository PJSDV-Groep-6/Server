// Server side C/C++ program to demonstrate Socket programming
#include <string>
#include <cstring>
#include <vector>
#include "headers/socketService.h"
#include "headers/bed.h"
#include "headers/schemerlamp.h"
#include "headers/deur.h"
#include "headers/muur.h"
bool STOP(char* buffer);

int main(int argc, char const* argv[]) {
    std::vector<meubel*> meubels;
    meubels.push_back(new schemerlamp(1, "schemerLamp", "../states.cpp", "../istates.cpp"));
    meubels.push_back(new deur(2, "deur", "../states.cpp", "../istates.cpp"));
    meubels.push_back(new bed(3, "bedLamp", "../states.cpp", "../istates.cpp"));
    meubels.push_back(new muur(4, "muur", "../states.cpp", "../istates.cpp"));
    int id = 0;
    char buffer[1024] = {0};
    std::string message;
    socketService server(8080);
    while (!STOP(buffer)) {
        server.sockAccept();
        server.parseInput(buffer);
        id = server.id;
        message = server.message;
        for(meubel* Meubel : meubels){
            Meubel->input(id, message);
            Meubel->check();
            Meubel->checkIState(Meubel->state);
        }
        if (message == "check") {
            for (int i = 0; i < meubels.size(); i++) {
                if (id == meubels[i]->geefID()) {
                    server.sockSend(meubels[i]->state);
                }
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
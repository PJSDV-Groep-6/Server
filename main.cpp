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
    meubels.push_back(new schemerlamp(1, "schemerLamp", "../states.cpp"));
    meubels.push_back(new deur(2, "deur", "../states.cpp"));
    meubels.push_back(new bed(3, "bedLamp", "../states.cpp"));
    meubels.push_back(new muur(4, "muur", "../states.cpp"));
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
        }
        if (message == "check") {
            for (int i = 0; i < meubels.size(); i++) {
                if (id == meubels[i]->geefID()) {
                    server.sockSend(meubels[i]->state);
                }
            }
        }
        else server.sockSend("ok");
        server.sockClose();
    }
    return 0;
}

bool STOP(char* buffer) {
    return strncmp(buffer, "STOP", 4) == 0;
}
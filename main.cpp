// Server side C/C++ program to demonstrate Socket programming
#include <string>
#include <cstring>
#include "headers/socketService.h"
#include "headers/bed.h"
#include "headers/schemerlamp.h"
#include "headers/deur.h"

bool STOP(char* buffer);
void endBuffer(char* buffer, size_t length);
void clearBuffer(char* buffer, const size_t length);

int main(int argc, char const* argv[]) {
    //Maak objecten aan voor elke type meubel
    bed bed1(3, "bedLamp", "states.txt");
    schemerlamp lamp1(1, "schemerLamp", "states.txt");
    deur deur1(2, "deur", "states.txt");
    const size_t bufferSize = 1024;
    char buffer[1024] = {0};
    int valread;
    int id = 0;
    std::string message;
    socketService server(8080); //start socket server op port 8080
    while (!STOP(buffer)) {
        server.sockAccept(); //wacht op socket connectie
        valread = server.sockRead(buffer);
        endBuffer(buffer, valread);
        std::istringstream receive(buffer);
        receive >> id >> message;
        //laat elk object de id en message processen
        lamp1.input(id, message);
        //bed processed anders om cross device bed en lamp te laten werken
        if (bed1.input(id, message)){
            //zet de lamp aan op basis van de message
            lamp1.zetState(true);
        }
        deur1.input(id, message);
        //check voor elk object de statefile en update relevante states
        lamp1.check();
        bed1.check();
        deur1.check();
        //stuur een reply terug op basis van id en message
        if (message == "check") {
            switch (id) {
                case 1:
                    server.sockSend(lamp1.state);
                    break;
                case 2:
                    server.sockSend(deur1.state);
                    break;
                case 3:
                    server.sockSend(bed1.state);
                    break;
                default:
                    server.sockSend("Unkown ID");
                    break;
            }
        }
        else server.sockSend("ok");
            //clear de buffer
            clearBuffer(buffer, bufferSize);
            //close de socket
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

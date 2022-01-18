// Server side C/C++ program to demonstrate Socket programming
#include <string>
#include <cstring>
#include <iostream>
#include "headers/socketService.h"
#include "headers/fileHandle.h"
#include "headers/bed.h"
#include "headers/schemerlamp.h"
#include "headers/deur.h"

bool STOP(char* buffer);
void endBuffer(char* buffer, size_t length);
void clearBuffer(char* buffer, const size_t length);
bool licht = false;


int main(int argc, char const* argv[]) {
    bed bed1(3, "bedLamp", "../states.cpp");
    schemerlamp lamp1(1, "schemerLamp", "../states.cpp");
    deur deur1(2, "deur", "../states.cpp");
    const size_t bufferSize = 1024;
    char buffer[1024] = {0};
    int valread;
    int id = 0;
    std::string message;
    socketService server(8080);
    while (!STOP(buffer)) {
        lamp1.check();
        bed1.check();
        deur1.check();
        server.sockAccept();
        valread = server.sockRead(buffer);
        endBuffer(buffer, valread);
        std::istringstream receive(buffer);
        receive >> id >> message;
        switch (id) {
            case 1:
                if (message == "check") {
                    server.sockSend(lamp1.state);
                } else if (message == "Beweging" && !licht) {
                    //send(new_socket, "licht", 9, 0);
                    lamp1.aan(true);
                    licht = true;
                    server.sockSend("ok");
                } else if (message == "Beweging" && licht) {
                    //send(new_socket, "thcil", 9, 0);
                    lamp1.aan(false);
                    licht = false;
                    server.sockSend("ok");
                } else server.sockSend("ok");
                break;
            case 2:
                if (message == "check") {
                    server.sockSend(deur1.state);
                } else if ((message == "insideClosed" || message == "outsideClosed")) {
                    //send(new_socket, "open", 9, 0);
                    deur1.open(true);
                } else if ((message == "insideOpen" || message == "outsideOpen")) {
                    //send(new_socket, "closed", 9, 0);
                    deur1.open(false);
                } else server.sockSend("ok");
                break;
            case 3:
                if (message == "check") {
                    server.sockSend(bed1.state);
                } else if (message == "switch") {
                    //send(new_socket, "licht", 9, 0);
                    //strcpy(schemerLamp, "thcil");
                    server.sockSend("ok");
                    bed1.toggleLed();
                    lamp1.toggleLed();
                } else if (message == "opgestaan") {
                    server.sockSend("ok");
                    //strcpy(schemerLamp, "licht");
                    lamp1.aan(true);
                    //statefile.modifyFileLine("schemerLamp", "schemerLamp 1 1");
                } else server.sockSend("ok");
                break;
            default:
                server.sockSend("Unkown ID");
                break;
            }
                //printf("%s\n", buffer);
                clearBuffer(buffer, bufferSize);
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
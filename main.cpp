// Server side C/C++ program to demonstrate Socket programming
#include <string>
#include <cstring>
#include <iostream>
#include "headers/socketService.h"
#include "headers/file_handle.h"
#include "headers/bed.h"
#include "headers/schemerlamp.h"

bool STOP(char* buffer);
void endBuffer(char* buffer, size_t length);
void readFile(std::string file);
void clearBuffer(char* buffer);

const char *deur = "close";
const char *schemerLamp = "thcil";
const char *bedLamp = "thcil";
bool licht = false;

file_handle statefile("../states.txt");

int main(int argc, char const* argv[]) {
    bed bed1(3, "bedLamp", "../states.txt");
    schemerlamp lamp1(1, "schemerLamp", "../states.txt");
    char buffer[1024] = {0};
    int valread;
    int id = 0;
    std::string message;
    socketService server(8080);
    while (!STOP(buffer)) {
        readFile("../states.txt");
        server.sockAccept();
        valread = server.sockRead(buffer);
        endBuffer(buffer, valread);
        std::istringstream receive(buffer);
        receive >> id >> message;
        switch (id) {
            case 1:
                if (message == "check") {
                    server.sockSend(schemerLamp);
                } else if (message == "Beweging" && !licht) {
                    //send(new_socket, "licht", 9, 0);
                    statefile.modify_file_line("schemerLamp", "schemerLamp 1");
                    licht = true;
                    server.sockSend("ok");
                } else if (message == "Beweging" && licht) {
                    //send(new_socket, "thcil", 9, 0);
                    statefile.modify_file_line("schemerLamp", "schemerLamp 0");
                    licht = false;
                    server.sockSend("ok");
                } else server.sockSend("ok");
                break;
            case 2:
                if (message == "check") {
                    server.sockSend(deur);
                } else if ((message == "insideClosed" || message == "outsideClosed") && deur == "close") {
                    //send(new_socket, "open", 9, 0);
                    statefile.modify_file_line("deur", "deur 1");
                } else if ((message == "insideOpen" || message == "outsideOpen") && deur == "open") {
                    //send(new_socket, "closed", 9, 0);
                    statefile.modify_file_line("deur", "deur 0");
                } else server.sockSend("ok");
                break;
            case 3:
                if (message == "check") {
                    server.sockSend(bedLamp);
                } else if (message == "switch") {
                    //send(new_socket, "licht", 9, 0);
                    schemerLamp = "thcil";
                    server.sockSend("ok");
                    bed1.toggleLed();
                    lamp1.toggleLed();
                } else if (message == "opgestaan") {
                    server.sockSend("ok");
                    schemerLamp = "licht";
                    statefile.modify_file_line("schemerLamp", "schemerLamp 1 1");
                } else server.sockSend("ok");
                break;
            default:
                server.sockSend("Unkown ID");
                break;
            }
                //printf("%s\n", buffer);
                clearBuffer(buffer);
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

void readFile(std::string file){
    std::fstream statefile;
    statefile.open(file, std::ios::in);
    if (statefile.is_open()) {
        std::string line;
        std::string state;
        std::string lock;
        bool brand;
        int value = 0;
        while (getline(statefile, line)) {
            std::istringstream stream(line);
            stream >> state >> value >> lock;
            //std::cout << state << " " << value << std::endl;
            if(lock == "0" && !brand) {
                if (state == "deur" && value == 1) {
                    deur = "open";
                } else if (state == "deur" && value == 0) deur = "close";
                if (state == "schemerLamp" && value == 1) {
                    schemerLamp = "licht";
                } else if (state == "schemerLamp" && value == 0) schemerLamp = "thcil";
                if (state == "bedLamp" && value == 1) {
                    bedLamp = "licht";
                } else if (state == "bedLamp" && value == 0) bedLamp = "thcil";
            }
            if (state == "brand" && value == 1) {
                deur = "open";
                schemerLamp = "licht";
//                statefile.modify_file_line("schemerlamp", "schemerLamp 1 1");
//                statefile.modify_file_line("deur", "deur 1 1");
//                statefile.modify_file_line("bedLamp", "bedLamp 1 1");
                brand = true;
            }
            else if (state == "brand" && value == 0){
                brand = false;
            }
        }
        statefile.close();
    }
}

void clearBuffer(char* buffer) {
    for (int i = 0; i <= sizeof(buffer); i++) {
        buffer[i] = 0;
    }
}
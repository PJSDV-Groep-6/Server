// Server side C/C++ program to demonstrate Socket programming
#include <string>
#include <cstring>
#include <iostream>
#include "socketService.h"
#include "file_handle.h"
#include "bed.h"

bool STOP(char* buffer);
void endBuffer(char* buffer, size_t length);
void readFile(std::string file);
bool toggleLed();
void clearBuffer(char* buffer) {
    for (int i = 0; i <= sizeof(buffer); i++) {
        buffer[i] = 0;
    }
}

const char *deur = "close";
const char *schemerLamp = "thcil";
const char *bedLamp = "thcil";
bool licht = false;
bool bedSwitch = false;

file_handle statefile("../states.cpp");
bed bed1(3, "bedLamp", "../states.cpp");
file_handle logboek("log.txt");

int main(int argc, char const* argv[]) {
    char buffer[1024] = {0};
    int valread;
    int id = 0;
    std::string message;
    socketService server(8080);
    while (!STOP(buffer)) {
        readFile("../states.cpp");
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
                    toggleLed();
                } else if (message == "opgestaan") {
                    server.sockSend("ok");
                    schemerLamp = "licht";
                    statefile.modify_file_line("schemerLamp", "schemerLamp 1 1");
                } else server.sockSend("ok");
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

bool toggleLed(){
    if (bedSwitch){
        //bed1.zetLed(false);
        statefile.modify_file_line("bedLamp", "bedLamp 0 0");
        statefile.modify_file_line("schemerLamp", "schemerLamp 0 0");
        logboek.append_line("Bedlamp is uit");
        bedSwitch = false;
    }
    else{
        //bed1.zetLed(true);
        statefile.modify_file_line("bedLamp", "bedLamp 1 0");
        statefile.modify_file_line("schemerLamp", "schemerLamp 0 0");
        logboek.append_line("Bedlamp is aan");
        bedSwitch = true;
    }
}

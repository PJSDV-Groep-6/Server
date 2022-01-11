// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string>
#include <string.h>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <limits>

#define PORT 8080

bool STOP(char* buffer);
void endBuffer(char* buffer, size_t length);
void readFile(std::string file);
void clearBuffer(char* buffer) {
    for (int i = 0; i <= sizeof(buffer); i++) {
        buffer[i] = 0;
    }
}

void modify_file_line(std::string path, int n_line, std::string newcontent) {

    std::fstream file{path, std::ios::out | std::ios::in};
    std::vector<std::string> lines{};
    std::string lineText{};
    // go to n_line
    for (int i = 0; i < n_line; i++) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    auto begin = file.tellg(); // cursor position of the beginning of the n_line
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // skip that n_line

    {
        std::fstream temp{"./temp.txt", std::ios::out};
        std::string templine{};
        while (getline(file, templine)) {
            temp << templine << "\n";
            std::cout << templine << "\n";
        }
    }
    file.clear();
    file.seekg(begin);
    file << newcontent;

    {
        std::fstream temp{"./temp.txt", std::ios::in};
        std::string templine{};
        while (getline(temp, templine)) {
            file << templine << "\n";
        }
        temp.close();
    }
    file.close();
}

const char *deur = "closed";
const char *schemerLamp = "thcil";
const char *bedLamp = "thcil";
bool licht = false;

int main(int argc, char const* argv[])
{
    int server_fd, new_socket, valread, connection;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char numberString[24] = {0};
    
    int id = 0;
    std::string message;

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
        &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr*)&address,sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (!STOP(buffer)) {
        readFile("../states.cpp");
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0){
            perror("accept");
            exit(EXIT_FAILURE);
        }
        valread = read(new_socket, buffer, 1024);
        endBuffer(buffer, valread);
        std::istringstream receive(buffer);
        receive >> id >> message;
        switch (id) {
            case 1:
                if (message == "check"){
                    send(new_socket, schemerLamp, 9, 0);
                }
                else if (message == "Beweging" && !licht) {
                    //send(new_socket, "licht", 9, 0);
                    modify_file_line("../states.cpp", 1, "schemerLamp 1 0\n");
                    licht = true;
                }
                else if (message == "Beweging" && licht) {
                    //send(new_socket, "thcil", 9, 0);
                    modify_file_line("../states.cpp", 1, "schemerLamp 0 0\n");
                    licht = false;
                }
                else send(new_socket, "ok", 9, 0);
            case 2:
                if (message == "check"){
                    send(new_socket, deur, 9, 0);
                }
                else if ((message == "insideClosed" || message == "outsideClosed") && deur == "closed") {
                    //send(new_socket, "open", 9, 0);
                    modify_file_line("../states.cpp", 2, "deur 1 0\n");
                }
                else if ((message == "insideOpen" || message == "outsideOpen") && deur == "open") {
                    //send(new_socket, "closed", 9, 0);
                    modify_file_line("../states.cpp", 2, "deur 0 0\n");
                }
                else send(new_socket, "ok", 9, 0);
            case 3:
                if (message == "check"){
                    send(new_socket, bedLamp, 9, 0);
                }
                else if (message == "1") {
                    //send(new_socket, "licht", 9, 0);
                    send(new_socket, "ok", 9, 0);
                    modify_file_line("../states.cpp", 0, "bedLamp 1 0\n");
                    modify_file_line("../states.cpp", 1, "schemerLamp 1 0\n");
                }
                else if (message == "2") {
                    //send(new_socket, "thcil", 9, 0);
                    send(new_socket, "ok", 9, 0);
                    modify_file_line("../states.cpp", 0, "bedLamp 0 0\n");
                    modify_file_line("../states.cpp", 1, "schemerLamp 0 0\n");
                }
                else send(new_socket, "ok", 9, 0);
        }

        printf("%s\n", buffer);
        clearBuffer(buffer);
        shutdown(new_socket, SHUT_RDWR);
        close(new_socket);
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
                } else if (state == "deur" && value == 0) deur = "closed";
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
                modify_file_line("../states.cpp", 1, "schemerLamp 1 1\n");
                modify_file_line("../states.cpp", 2, "deur 1 1\n");
                brand = true;
            }
            else if (state == "brand" && value == 0){
                brand = false;
            }
        }
        statefile.close();
    }
}

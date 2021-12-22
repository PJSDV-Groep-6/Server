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

#define PORT 8080

bool STOP(char* buffer);
void endBuffer(char* buffer, size_t length);
void clearBuffer(char* buffer) {
    for (int i = 0; i <= sizeof(buffer); i++) {
        buffer[i] = 0;
    }
}

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
    bool licht = false;
    std::fstream statefile;
    while (!STOP(buffer)) {
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
                if (message == "Beweging" && !licht) {
                    send(new_socket, "licht", 9, 0);
                    licht = true;
                }
                else if (message == "Beweging" && licht) {
                    send(new_socket, "thcil", 9, 0);
                    licht = false;
                }
            case 2:
                if (message == "0" || message == "2") {
                    send(new_socket, "1", 2, 0);
                }
                if (message == "1" || message == "3") {
                    send(new_socket, "0", 2, 0);
                }
            case 3:
                if (message == "1") {
                    send(new_socket, "licht", 9, 0);
                }
                else if (message == "0") {
                    send(new_socket, "thcil", 9, 0);
                }
        }
        statefile.open("states.txt", std::ios::in);
        if (statefile.is_open()) {
            std::string line;
            std::string state;
            int value = 0;
            while (getline(statefile, line)) {
                std::istringstream stream(line);
                stream >> state >> value;
                //std::cout << state << " " << value << std::endl;
                //if(state == "drukKnopDeur")
            }
        }
        //send(new_socket, buffer, 1024, 0);
        printf("%s\n", buffer);
        clearBuffer(buffer);
        statefile.close();
        shutdown(new_socket, SHUT_RDWR);
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

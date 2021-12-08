// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <string>
#include <stdexcept>

#include "LinkedList.cpp"

#define PORT 8080

bool STOP(char* buffer);
void endBuffer(char* buffer, size_t length);

int main(int argc, char const* argv[])
{
    int server_fd, new_socket, valread, connection;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char numberString[24] = {0};
    
    LinkedList<int> messageList;
    Node<int>* node;
    int id = 0, message = 0;

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
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0){
            perror("accept");
            exit(EXIT_FAILURE);
        }
        valread = read(new_socket, buffer, 1024);
        endBuffer(buffer, valread);
        sscanf(buffer, "%d %d", &id, &message);
        if (id == 2 && message == 0) {
            messageList.addNode(3, 2);
        }
        strcpy(buffer, "");
        while((node = messageList.removeNode(id)) != NULL){
            sprintf(numberString, "%d ", node->getData());
            strcat(buffer, numberString);
            delete node;
        }
        send(new_socket, buffer, 1024, 0);
        printf("%s\n", buffer);
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

// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const* argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    string message;
    char* hello = "Hello from client";
    char buffer[1024] = { 0 };
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    for (int i = 0, i < 5, i++;) {
        if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            printf("\nConnection Failed \n");
            return -1;
        }
        std::cin >> message;
        send(sock, message, strlen(message), 0);
        //printf("Hello message sent\n");
        valread = read(sock, buffer, 1024);
        printf("%s\n", buffer);
        shutdown(sock, SHUT_RDWR);
    }
    return 0;
}

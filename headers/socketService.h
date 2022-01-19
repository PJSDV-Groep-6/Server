#ifndef SERVER_SOCKETSERVICE_H
#define SERVER_SOCKETSERVICE_H

#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <stdexcept>
#include <unistd.h>
#include <sstream>

using namespace std;

class socketService {
public:
    socketService(int);
    void sockSend(const char*);
    void sockClose();
    void parseInput(char[]);
    void sockAccept();
    int id;
    string message;
private:
    void endBuffer(char* buffer, size_t length);
    int sockRead(char[]);
    int valread;
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    int PORT;
};


#endif //SERVER_SOCKETSERVICE_H

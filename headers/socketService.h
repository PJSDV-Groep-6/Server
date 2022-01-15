#ifndef SERVER_SOCKETSERVICE_H
#define SERVER_SOCKETSERVICE_H

#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>headers
#include <stdexcept>
#include <unistd.h>

using namespace std;

class socketService {
public:
    socketService(int);
    void sockAccept();
    int sockRead(char[]);
    void sockSend(const char*);
    void sockClose();
private:
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    int PORT;
};


#endif //SERVER_SOCKETSERVICE_H

#ifndef SOCKET_H
#define SOCKET_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <cerrno>
#include <stdlib.h>
#include <iostream>
#include <arpa/inet.h>
struct Message {
//    size_t lenght_buffer = 1024;
    char text[1024];
    pthread_mutex_t mutex1;
};
class Socket
{


public:
    int fd = 0;
    Socket(const sockaddr_in& address);
    ~Socket();
    sockaddr_in make_ip_address(const std::string& ip_address, int port);
    void send_to(Message message, sockaddr_in remote_address);
    void recive_from(Message message, sockaddr_in local_address);
};


#endif // SOCKET_H

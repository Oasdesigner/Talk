#ifndef SOCKET_H
#define SOCKET_H
#pragma once
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <cerrno>
#include <stdlib.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

struct Message {
//    size_t lenght_buffer = 1024;
    char text[1024];
};
class Socket
{
public:
    int fd;
    Socket() = default;
    Socket(const sockaddr_in& address);
    ~Socket();
    Socket(const Socket&) = delete;
    Socket& operator =(const Socket&) = delete;
    Socket(Socket&& rhs) noexcept;
    Socket& operator =(Socket&& rhs) noexcept;

    sockaddr_in make_ip_address(const std::string& ip_address, int port);
    void send_to(Message message, sockaddr_in remote_address);
    void recive_from(Message message, sockaddr_in local_address);
};


#endif // SOCKET_H

#include <QCoreApplication>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "socket.h"

sockaddr_in make_ip_address(const std::string& ip_address,int port){

    sockaddr_in address{};    // Porque se recomienda inicializar a 0
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_aton(ip_address.c_str(), &address.sin_addr);
    return address;
}

void translate(std::string aux,Message message_main);

// Estructura de los mensajes

void write(Message& message_main){

    std::string aux = "";
    std::getline(std::cin,aux);
    memset(&message_main, 0, sizeof(message_main));
    int sz = aux.copy(message_main.text, aux.size());
    message_main.text[sz] = '\0';
}


int main()
{
    sockaddr_in local_address_main = make_ip_address("127.0.0.1",32653);
    sockaddr_in remote_address_main = make_ip_address("127.0.0.3",32654);
    Socket socket_main(local_address_main);


    Message message_main;
    write(message_main);


    socket_main.send_to(message_main,remote_address_main);
    socket_main.recive_from(message_main,local_address_main);


    std::cout<<"BIEN" << std::endl;

    return 0;
}

#include "socket.h"




Socket::Socket(const sockaddr_in& address)
{

   fd = socket(AF_INET, SOCK_DGRAM, 0);
   if (fd < 0) {
     std::cerr << "no se pudo crear el socket: " << std::strerror(errno) << '\n';
     throw std::system_error(errno, std::system_category(), "Error al crear el socket");
    }

   int result = bind(fd, reinterpret_cast <const sockaddr*>(&address), sizeof(address));
   if (result < 0) {
      std::cerr << "falló bind: " << std::strerror(errno) << '\n';
      throw 5;    // Error. Termina el programa siempre con un valor > 0
   }

}
Socket::~Socket()
{
}

void Socket::send_to(Message message, sockaddr_in remote_address){

    int result = sendto(fd,message.text,sizeof(message.text),0,reinterpret_cast<const sockaddr*>(&remote_address),sizeof(remote_address));
    if (result < 0) {
        std::cerr << "falló sendto: " << std::strerror(errno) << '\n';
        throw 6;
    }
}

void Socket::recive_from(Message message, sockaddr_in local_address){

    socklen_t src_len = sizeof(local_address);

    int result = recvfrom(fd, &message, sizeof(message), 0,reinterpret_cast<sockaddr*>(&local_address), &src_len);
    if (result < 0) {
        std::cerr << "falló recvfrom: " << std::strerror(errno) << '\n';
        throw 8;
    }
    std::cout<<"Recived -> "<<message.text;
}




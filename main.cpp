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
void write(Message& message_main){

    std::string aux = "";
    std::cout<<">";
    std::getline(std::cin,aux);
    memset(&message_main, 0, sizeof(message_main));
    int sz = aux.copy(message_main.text, aux.size());
    message_main.text[sz] = '\0';
}
std::string menu(std::string parameter){
    std::string aux = "";
    std::cout<<"127.0.0.";
    std::getline(std::cin,aux);
    std::string final = parameter + aux;
    return final;
}
int choose_port(std::string parameter){
    std::string aux = "";
    std::cout<<"3265";
    std::getline(std::cin,aux);
    std::string aux2 = parameter + aux;
    int final = atoi(aux2.c_str());
    std::cout<<final;
    return final;

}
int main()
{

    //select ip and port
    std::string ip_local="127.0.0.";
    std::string ip_remote="127.0.0.";
    std::string port_local_var="3265";
    std::string port_remote_var="3265";
    ip_local = menu(ip_local);
    int port_local=choose_port(port_local_var);
    ip_remote = menu(ip_remote);
    int port_remote = choose_port(port_remote_var);

    //create sockets
    sockaddr_in local_address_main = make_ip_address(ip_local,port_local);
    sockaddr_in remote_address_main = make_ip_address(ip_remote,port_remote);
    Socket socket_main(local_address_main);

    bool condition=true;
    //Send and recieve messages
    while(condition==true){
        Message message_main;
        write(message_main);

        socket_main.send_to(message_main,remote_address_main);
        socket_main.recive_from(message_main,local_address_main);

        if(strcmp(message_main.text,"EXIT")==0)
            condition=false;

    }

    std::cout<<"Concluido con éxito" << std::endl;

    return 0;
}

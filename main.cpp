#include <QCoreApplication>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "socket.h"
#include <thread>
#include <pthread.h>
#include <iostream>
std::string Global_name;
struct ip_config{
    std::string ip_local="127.0.0.";
    std::string ip_remote="127.0.0.";
    std::string port_local_var="3265";
    std::string port_remote_var="3265";
};
sockaddr_in make_ip_address(const std::string& ip_address,int port){

    sockaddr_in address{};    // Porque se recomienda inicializar a 0
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_aton(ip_address.c_str(), &address.sin_addr);
    return address;
}
void write(Message& message_main,bool condition){

    if(condition){
        std::string aux5 = "";
        std::cout<<">";
        std::getline(std::cin,aux5);
        aux5 = Global_name + ":" + aux5;
        memset(&message_main, 0, sizeof(message_main));
        int sz = aux5.copy(message_main.text, aux5.size());
        message_main.text[sz] = '\0';
    }else{
        std::string aux5 = "##12344321##!asd3sfg2d";
        memset(&message_main, 0, sizeof(message_main));
        int sz = aux5.copy(message_main.text, aux5.size());
        message_main.text[sz] = '\0';
    }

}
std::string menu(std::string parameter){
    bool condition=true;
    std::string final;
    while (condition){
        std::string aux = "";
        std::cout<<"127.0.0.";
        std::cin>>aux;
        int aux1 = atoi(aux.c_str());
        if((aux1<10)&&(aux1>0)){
            final = parameter + aux;
            condition=false;
        }else{
            std::cout<<"Error al coger la ip, introduzca una dirección valida"<<std::endl;
        }
    }
    return final;
}
std::string choose_port(std::string parameter){
    bool condition=true;
    std::string aux2;
    while(condition){
        std::string aux = "";
        std::cout<<"3265";
        std::cin>>aux;
        int aux3 = atoi(aux.c_str());
        if((aux3>0)&&(aux3<10)){
            aux2 = parameter + aux;
            condition=false;
        }else{
            std::cout<<"Error al elegir el puerto, ponga un numero valido"<<std::endl;
        }
    }
    return aux2;

}
void call_sent_to (Socket socket_main,sockaddr_in remote_address_main){
     bool condition = true;
     Message message_main;
     std::cin.ignore();
     while(condition==true){
         write(message_main,true);
         std::string compare = Global_name + ":" + "\\quit";
         if(message_main.text == compare){
             write(message_main,false);
             condition=false;
             socket_main.send_to(message_main,remote_address_main);
         }else
            socket_main.send_to(message_main,remote_address_main);
     }
}
void call_recieve_from (Socket socket_main,sockaddr_in local_address_main){

    bool condition = true;
    Message message_main;
    while(condition){
        socket_main.recive_from(message_main,local_address_main);
        std::cout<<message_main.text<<std::endl;
    }
}
void request_cancelation(std::thread& thread){

        pthread_cancel(thread.native_handle());
}
void personalizadoS(ip_config& config){
    std::cout<<"Ip Local"<<std::endl;
    config.ip_local = menu(config.ip_local);
    std::cout<<"Ip Remota"<<std::endl;
    config.ip_remote = menu(config.ip_remote);
    std::cout<<"Puerto Local"<<std::endl;
    config.port_local_var = choose_port(config.port_local_var);
    std::cout<<"Puerto remoto"<<std::endl;
    config.port_remote_var = choose_port(config.port_remote_var);
}
void personalizadoA(ip_config& config){
    std::cout << "Ip Local"<<std::endl;
    std::cin  >> config.ip_local;
    std::cout << "Ip Remota"<<std::endl;
    std::cin  >> config.ip_remote;
    std::cout << "Puerto Local"<<std::endl;
    std::cin  >> config.port_local_var;
    std::cout << "Puerto remoto"<<std::endl;
    std::cin  >> config.port_remote_var;
}
void defecto(ip_config& config){
    int op=-1;
    while(op!=0){
        std::cout<<"1.- Host"<<std::endl;
        std::cout<<"2.- Join to host"<<std::endl;
        std::cin>>op;
        switch (op) {
        case 1:
            config.ip_local = "127.0.0.1";
            config.ip_remote = "127.0.0.2";
            config.port_local_var = "32651";
            config.port_remote_var = "32652";
            op=0;
            break;
        case 2:
            config.ip_local = "127.0.0.2";
            config.ip_remote = "127.0.0.1";
            config.port_local_var = "32652";
            config.port_remote_var = "32651";
            op=0;
            break;
        default:
            std::cout<<"Error al elegir la opción"<<std::endl;
            break;
        }
    }
}

void menu_principal(ip_config& config){
    int op=-1;
    while (op!=0){
        std::cout<<"Elija la configuración"<<std::endl;
        std::cout<<"1.- Por defecto"<<std::endl;
        std::cout<<"2.- Personalizado sencillo"<<std::endl;
        std::cout<<"3.- Personalizado avanzado"<<std::endl;
        std::cout<<"0.- Ni siquiera quería estar aquí"<<std::endl;
        std::cin>>op;
        switch(op){
           case 1:
              defecto(config);
              op=0;
              break;
           case 2:
              personalizadoS(config);
              op=0;
              break;
           case 3:
              personalizadoA(config);
              op=0;
              break;
           case 0:
              std::cout<< "Saliendo..." << std::endl;
              op=0;
            break;
           default:
              std::cout<<"Error al elegir la opción, elija un valor valido"<<std::endl;
              break;

        }
    }

}


int main()
{
    //select ip and port
    ip_config config;
    menu_principal(config);

    int aux= atoi(config.port_local_var.c_str());
    int aux1= atoi(config.port_remote_var.c_str());
    std::cout<<"Introduzca su nombre"<<std::endl;
    std::cin>>Global_name;
    //create sockets
    sockaddr_in local_address_main = make_ip_address(config.ip_local,aux);
    sockaddr_in remote_address_main = make_ip_address(config.ip_remote,aux1);
    Socket socket_main(local_address_main);
    //Send and recieve messages

       try{
            std::thread thread1(&call_sent_to,socket_main,remote_address_main);
            std::thread thread2(&call_recieve_from,socket_main,local_address_main);
            thread1.join();
            request_cancelation(thread2);
            thread2.join();
        }
        catch(std::system_error& e) {
            std::cerr << program_invocation_name << e.what() << "Error de sistema\n";
            return 2;
        }

        catch(std::bad_alloc& e) {
            std::cerr << program_invocation_name << e.what() << "Memoria insuficiente\n";
            return 1;
        }
        catch (...) {
            std::cerr << program_invocation_name << strerror(errno) << "Error desconocido\n";
            return 4;
        }


    std::cout<<"Concluido con éxito" << std::endl;

    return 0;
}

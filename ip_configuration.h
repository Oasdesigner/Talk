#ifndef IP_CONFIGURATION_H
#define IP_CONFIGURATION_H
#pragma once
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <pthread.h>
#include <arpa/inet.h>


class ip_configuration
{
private:
    std::string ip_local;
    std::string ip_remote;
    std::string port_local;
    std::string port_remote;
public:
    ip_configuration();
    ip_configuration(std::string ip_local_var,std::string ip_remote_var,std::string port_local_var,std::string port_remote_var);
    //get
    std::string get_ip_local();
    std::string get_ip_remote();
    std::string get_port_local();
    std::string get_port_remote();
    //set
    void set_ip_local(std::string ip_local_var);
    void set_ip_remote(std::string ip_remote_var);
    void set_port_local(std::string port_local_var);
    void set_port_remote(std::string port_remote_var);
    //functions
};

#endif // IP_CONFIGURATION_H

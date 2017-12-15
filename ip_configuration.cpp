#include "ip_configuration.h"

ip_configuration::ip_configuration()
{
    ip_configuration::ip_local = "";
    ip_configuration::ip_remote = "";
    ip_configuration::port_local = "";
    ip_configuration::port_remote = "";
}
//GET
std::string ip_configuration::get_ip_local(){
    return ip_configuration::ip_local;
}
std::string ip_configuration::get_ip_remote(){
    return ip_configuration::ip_remote;
}
std::string ip_configuration::get_port_local(){
    return ip_configuration::port_local;
}
std::string ip_configuration::get_port_remote(){
    return ip_configuration::port_remote;
}

//Set
void ip_configuration::set_ip_local(std::string ip_local_var){
    ip_configuration::ip_local=ip_local_var;
}
void ip_configuration::set_ip_remote(std::string ip_remote_var){
    ip_configuration::ip_remote=ip_remote_var;
}
void ip_configuration::set_port_local(std::string port_local_var){
    ip_configuration::port_local=port_local_var;
}
void ip_configuration::set_port_remote(std::string port_remote_var){
    ip_configuration::port_remote=port_remote_var;
}
//functions

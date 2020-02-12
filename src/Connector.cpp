#include "../header/Connector.hpp"

Connector::Connector(char* connectorType){
    type = std::string(connectorType);
}

char* Connector::getPath(){
    char* test = NULL;
    return test;
}

char** Connector::getArgs(){
    char* args[1];
    args[0] = " ";
    args[1] = NULL;
    return args;
}

std::string Connector::cmdString(){
    return type;
}
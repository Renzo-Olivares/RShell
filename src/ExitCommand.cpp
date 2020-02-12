#include "../header/ExitCommand.hpp"

ExitCommand::ExitCommand(char* exitex){
    type = std::string(exitex);
}

char* ExitCommand::getPath(){
    char* test = NULL;
    return test;
}

char** ExitCommand::getArgs(){
    char* args[1];
    args[0] = " ";
    args[1] = NULL;
    return args;
}

std::string ExitCommand::cmdString(){
    return type;
}
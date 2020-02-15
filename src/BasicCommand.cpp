#include "../header/BasicCommand.hpp"

BasicCommand::BasicCommand(char* execToken, char* argToken){
    command.push_back(execToken);
    command.push_back(argToken);
    command.push_back(NULL);
}

char* BasicCommand::getPath(){
    return command[0];
}

char** BasicCommand::getArgs(){
    return command.data();
}

bool BasicCommand::isMultiple(){
    return false;
}

std::string BasicCommand::cmdString(){
    return "cmd";
}
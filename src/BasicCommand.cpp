#include "../header/BasicCommand.hpp"

#include <iostream>

BasicCommand::BasicCommand(char execToken[], char argToken[]){
    executable = execToken;
    int n = strlen(argToken);
    char* const args[n] = {argToken};
    char allFlag[1] = {'a'};
    char *const flags[2] = {allFlag};
    char *const *lsArgs = flags;
    arguments = lsArgs;
    std::cout << "argtoken size " << n << std::endl;
    std::cout << "exectoken " << execToken << std::endl;
    std::cout << "argtoken " << argToken << std::endl;
    std::cout << "allflag " << allFlag << std::endl;
    std::cout << "final arguments being sent " << *arguments << std::endl;
}

const char* BasicCommand::getPath(){
    return executable;
}

char* const* BasicCommand::getArgs(){
    return arguments;
}

std::string BasicCommand::cmdString(){
    return getPath();
}
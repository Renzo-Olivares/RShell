#ifndef BASICCOMMAND_HPP
#define BASICCOMMAND_HPP

#include "../header/Command.hpp"
#include <cstring>

class BasicCommand : public Command {
    private:
        const char *executable;
        char* const* arguments;
    public:
        BasicCommand(char execToken[], char argToken[]);
        const char* getPath();
        char* const* getArgs();
        virtual std::string cmdString();
};

#endif /* BASICCOMMAND_HPP */
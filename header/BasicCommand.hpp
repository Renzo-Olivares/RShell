#ifndef BASICCOMMAND_HPP
#define BASICCOMMAND_HPP

#include "../header/Command.hpp"
#include <vector>

class BasicCommand : public Command {
    private:
        std::vector<char*> command;
    public:
        BasicCommand(char* execToken, char* argToken);
        char* getPath();
        char** getArgs();
        bool isMultiple();
        virtual std::string cmdString();
};

#endif /* BASICCOMMAND_HPP */
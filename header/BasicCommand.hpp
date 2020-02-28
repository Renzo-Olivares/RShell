#ifndef BASICCOMMAND_HPP
#define BASICCOMMAND_HPP

#include "../header/Command.hpp"
#include <vector>

class BasicCommand : public Command {
    private:
        std::vector<char*> command;
    public:
        BasicCommand(char* execToken, char* argToken);
        virtual char* getPath();
        virtual char** getArgs();
        virtual std::string cmdString();
        std::vector<char*> getRawCmd();
};

#endif /* BASICCOMMAND_HPP */
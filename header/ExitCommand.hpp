#ifndef EXITCOMMAND_HPP
#define EXITCOMMAND_HPP

#include "../header/Command.hpp"

class ExitCommand : public Command {
    private:
        std::string type;
    public:
        ExitCommand(char* exitex);
        char* getPath();
        char** getArgs();
        virtual std::string cmdString();
};

#endif /* EXITCOMMAND_HPP */
#ifndef EXITCOMMAND_HPP
#define EXITCOMMAND_HPP

#include "../header/Command.hpp"

class ExitCommand : public Command {
    private:
        std::string type;
    public:
        ExitCommand(char* exitex);
        virtual char* getPath();
        virtual char** getArgs();
        virtual bool isMultiple();
        virtual std::string cmdString();
};

#endif /* EXITCOMMAND_HPP */
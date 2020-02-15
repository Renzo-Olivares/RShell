#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>

class Command{
    public:
        Command(){};
        virtual std::string cmdString() = 0;
        virtual char* getPath() = 0;
        virtual char** getArgs() = 0;
        virtual bool isMultiple() = 0;
        virtual void addCmd(Command* cmd){};
};

#endif /* COMMAND_HPP */
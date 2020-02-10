#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <queue>

class Command{
    public:
        Command(){};
        virtual std::string cmdString() = 0;
        virtual const char* getPath() = 0;
        virtual char* const* getArgs() = 0;
};

#endif /* COMMAND_HPP */
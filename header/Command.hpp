#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <queue>
#include <vector>

class Command{
    public:
        Command(){};
        virtual std::string cmdString() = 0;
        virtual char* getPath() = 0;
        virtual char** getArgs() = 0;
        virtual std::vector<char*> getRawCmd(){};
};

#endif /* COMMAND_HPP */
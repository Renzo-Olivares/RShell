#ifndef COMMANDQUEUE_HPP
#define COMMANDQUEUE_HPP

#include "../header/Command.hpp"
#include <queue>

class CommandQueue : public Command {
    private:
        std::queue<Command*> commandList;
    public:
        char* getPath();
        char** getArgs();
        void addQueue(std::queue<Command*> cmdQ);
        void addCmd(Command* command);
        void popCmd();
        bool isEmpty();
        void clear();
        virtual std::string cmdString();
};

#endif /* COMMANDQUEUE_HPP */
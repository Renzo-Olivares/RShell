#ifndef COMMANDQUEUE_HPP
#define COMMANDQUEUE_HPP

#include "../header/Command.hpp"
#include <queue>

class CommandQueue : public Command {
    private:
        std::queue<Command*> commandList;
    public:
        virtual char* getPath();
        virtual char** getArgs();
        virtual void addQueue(std::queue<Command*> cmdQ);
        virtual void addCmd(Command* command);
        virtual std::string cmdString();
        virtual bool isMultiple();
        void popCmd();
        bool isEmpty();
        void clear();
        Command* getFront();
};

#endif /* COMMANDQUEUE_HPP */
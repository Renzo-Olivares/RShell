#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include "../header/Command.hpp"
#include "../header/BasicCommand.hpp"
#include <queue>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

class Executor{
    private:
        std::queue<Command*> commandQueue;
    public:
        Executor(std::queue<Command*> cmdQueue);
        void runCmds();
        /*int newChild();
        void pauseParent();*/
};

#endif /* EXECUTOR_HPP */
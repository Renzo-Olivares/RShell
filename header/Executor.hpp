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
        int child_status;
    public:
        Executor(std::queue<Command*> cmdQueue);
        void runCmds();
};

#endif /* EXECUTOR_HPP */
#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include "../header/Command.hpp"
#include "../header/BasicCommand.hpp"
#include "../header/CommandQueue.hpp"
#include "../header/Parser.hpp"
#include <queue>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

class Executor{
    private:
        CommandQueue* cmdList;
        int child_status;
        bool bracketError;
    public:
        Executor(CommandQueue* cmdQueue);
        int runCmds();
        int getLastChildStatus();
        bool runTestCmd();
};

#endif /* EXECUTOR_HPP */
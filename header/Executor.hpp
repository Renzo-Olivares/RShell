#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include "../header/Command.hpp"
#include "../header/BasicCommand.hpp"
#include "../header/CommandQueue.hpp"
#include <queue>
#include <sys/wait.h>
#include <unistd.h>

class Executor{
    private:
        CommandQueue* cmdList;
        int child_status;
    public:
        Executor(CommandQueue* cmdQueue);
        int runCmds();
        int getLastChildStatus();
};

#endif /* EXECUTOR_HPP */
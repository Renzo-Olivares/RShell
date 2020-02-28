#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include "../header/Command.hpp"
#include "../header/BasicCommand.hpp"
#include "../header/Parser.hpp"
#include <queue>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

class Executor{
    private:
        int child_status;
        bool bracketError;
        bool andflag;
        bool orflag;
        bool exitflag;
    public:
        Executor();
        int runCmds(Command* cmd);
        int getLastChildStatus();
        bool runTestCmd(Command* cmd);
        void inOrder(Node* cmndNode);
        bool isExit();
};

#endif /* EXECUTOR_HPP */
#include "../header/Executor.hpp"
#include "../header/Command.hpp"
#include "../header/BasicCommand.hpp"

#include <queue>

int main()
{
    std::queue<Command*> cmdQueue;
    char* cmndLs = "ls";
    char* allFlag = "-al";
    Command* test = new BasicCommand(cmndLs, allFlag);
    cmdQueue.push(test);
    Executor runner = Executor(cmdQueue);
    runner.runCmds();
    return 0;
}
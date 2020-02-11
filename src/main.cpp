#include "../header/Executor.hpp"
#include "../header/Command.hpp"
#include "../header/BasicCommand.hpp"
#include "../header/Parser.hpp"

#include <queue>

int main()
{
    /*
    std::queue<Command*> cmdQueue;
    char* cmndLs = "ls";
    char* allFlag = "-al";
    char* noFlag = "-a";
    Command* test = new BasicCommand(cmndLs, allFlag);
    Command* test2 = new BasicCommand(cmndLs, noFlag);
    cmdQueue.push(test);
    cmdQueue.push(test2);
    Executor runner = Executor(cmdQueue);
    runner.runCmds();
    */
   Parser analyzer = Parser();
   analyzer.run();
    return 0;
}
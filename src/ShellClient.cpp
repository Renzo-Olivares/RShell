#include "../header/ShellClient.hpp"

ShellClient::ShellClient(){
    init();
}

void ShellClient::init(){
/*  Executor test
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
    std::queue<Command*> cmdQueue = analyzer.getParsedCmds();
    Executor runner = Executor(cmdQueue);
    runner.runCmds();
   //Command* commandQueue = new CommandQueue();
   //commandQueue.add(analyzer.getParsedCmds());
/*
    
*/
}
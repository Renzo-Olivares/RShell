#include "../header/ShellClient.hpp"

ShellClient::ShellClient(){
    //while exit flag false
    while(!exit){
        init();
        //UserInput rawInput = UserInput();
        //Parser analyzer = Parser(rawInput.getInput());
        //analyzer.run();
        //Command* commandQueue = new CommandQueue();
        //commandQueue.add(analyzer.getParsedCmds());
        //Executor runner = Executor();
        //runner.runCmds();
        /*
            create exit command object, if executor encounters then immediately return and set exit flag to true
        */
    }
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
/*
    Parser analyzer = Parser("echo A && echo B");
    analyzer.run();
    std::queue<Command*> cmdQueue = analyzer.getParsedCmds();
    Executor runner = Executor(cmdQueue);
    runner.runCmds();
*/
   //Command* commandQueue = new CommandQueue();
   //commandQueue.add(analyzer.getParsedCmds());
   UserInput rawInput = UserInput();
}
#include "../header/ShellClient.hpp"

ShellClient::ShellClient(){
    while(!exit){
        init();
    }
}

void ShellClient::init(){
    UserInput rawInput = UserInput();
    Parser analyzer = Parser(rawInput.getInput());
    analyzer.run();
    //Command* commandQueue = new CommandQueue();
    //commandQueue.add(analyzer.getParsedCmds());
    std::queue<Command*> cmdQueue = analyzer.getParsedCmds();
    Executor runner = Executor(cmdQueue);
    exit = runner.runCmds() == 0? false: true;
}
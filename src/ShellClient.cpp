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
    CommandQueue* cmdQ = new CommandQueue();
    cmdQ->addQueue(analyzer.getParsedCmds());
    Executor runner = Executor(cmdQ);
    exit = runner.runCmds() == 0? false: true;
}
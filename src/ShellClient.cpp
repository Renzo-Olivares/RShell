#include "../header/ShellClient.hpp"

ShellClient::ShellClient(){
    exit = false;
    
    while(!exit){
        init();
    }
}

void ShellClient::init(){
    UserInput rawInput = UserInput();
    Parser analyzer = Parser(rawInput.getInput());
    analyzer.run();
    Node* cmndTree = analyzer.getParsedCmndTree();
    Executor runner = Executor();
    runner.inOrder(cmndTree);
    exit = runner.isExit() ? true: false;
}
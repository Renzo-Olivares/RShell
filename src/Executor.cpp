#include "../header/Executor.hpp"

Executor::Executor(CommandQueue* cmdQueue){
    cmdList = cmdQueue;
    bracketError = false;
}

int Executor::runCmds(){
    while(!cmdList->isEmpty()){
        pid_t child_pid; 
        pid_t wait_child; //pid returned by waitpid

        if((cmdList->getFront())->isMultiple()){
            Executor subrunner = Executor((CommandQueue* ) cmdList->getFront());
            int exit = subrunner.runCmds();
            if(exit != 0){
                cmdList->clear();
                return -1;
            }
            cmdList->popCmd(); ///pop commandqueue 
            child_status = subrunner.getLastChildStatus();
            continue;
        }

        if (cmdList->cmdString() != "cmd"){
            if(cmdList->cmdString() == "&&"){
                if(child_status == 0){
                    cmdList->popCmd(); //pop connector
                    continue;
                }else{
                    cmdList->popCmd(); //pop connector
                    cmdList->popCmd(); //pop next command
                    continue;
                }
            }else if(cmdList->cmdString() == "||"){
                if(child_status != 0){ //last command was not successful
                    cmdList->popCmd(); //pop connector
                    continue;
                }else{ //last command was successful
                    cmdList->popCmd(); //pop connector
                    cmdList->popCmd(); //pop next command
                    continue;
                }
            }else if(cmdList->cmdString() == "exit"){
                //break everythig and return immediately
                cmdList->clear();
                return -1;
            }else{
                cmdList->popCmd(); //pop connector
                continue;
            }
        }else{
            if(std::string(cmdList->getPath()) == "test" || std::string(cmdList->getPath()) == "["){
                //run test command
                bool fileFound  = runTestCmd();
                cmdList->popCmd();
                if(bracketError){
                    child_status = 256;
                    std::cout << "Command error" << std::endl;
                    bracketError = false;
                }else if(!fileFound){
                    child_status = 256;
                    std::cout << "(False)" << std::endl; 
                }else {
                    child_status = 0;
                    std::cout << "(True)" << std::endl;
                }
                continue;
            }
        }

        child_pid = fork();

        if(child_pid == 0){//fork() returns 0 to the child process
            execvp(cmdList->getPath(), cmdList->getArgs());


            //if child process reaches here execvp must have failed
            perror("execvp");
            exit(1);
        }
        else{//fork() returns process id of child process
            if(child_pid == (pid_t)(-1)){
                exit(1);
            }else{
                wait_child = waitpid(child_pid,&child_status,0);
            }
        }
        cmdList->popCmd();
    }
    return 0;
}

int Executor::getLastChildStatus(){
    return child_status;
}

bool Executor::runTestCmd(){
    std::vector<char*> testvec = (cmdList->getFront())->getRawCmd();
    Parser subParser = Parser("null");
    struct stat sb;
    std::string fullArgString = testvec.at(1);
    std::string testFlag = "-e";
    char* testArgs;
    int backPos = fullArgString.length() - 1;
    
    if(std::string(cmdList->getPath()) == "["){
        
        if(fullArgString.at(backPos) != ']'){
            bracketError = true;
            perror("bash");
            return NULL;
        }
        //trim bracket from args
        fullArgString.pop_back();
    }

    if(fullArgString.at(0) == '-'){
        testFlag = "-" + fullArgString[1];
        fullArgString = fullArgString.substr(3);
    }

    fullArgString = subParser.whitespaceTrimLt(fullArgString);
    fullArgString = subParser.popQuotes(fullArgString);
    testArgs = subParser.characterize(fullArgString);
    stat(testArgs, &sb);
    //test command logic
    if(testFlag == "-f"){
        switch(sb.st_mode & S_IFMT){
            case S_IFREG:             
                return true;
            default:                    
                return false;
        }
    }else if(testFlag == "-d"){
        switch(sb.st_mode & S_IFMT){
            case S_IFDIR:               
                return true;
            default:                  
                return false;
        }
    }else{
        switch(sb.st_mode & S_IFMT){
            case S_IFDIR:            
                return true;
            case S_IFREG:             
                return true;
            default:                      
                return false;
        }
    }
}
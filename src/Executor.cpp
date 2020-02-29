#include "../header/Executor.hpp"

Executor::Executor(){
    bracketError = false;
    andflag = false;
    orflag = false;
    exitflag = false;
}

int Executor::runCmds(Command* cmd){

        pid_t child_pid; 
        pid_t wait_child; //pid returned by waitpid

        if(std::string(cmd->getPath()) == "test" || std::string(cmd->getPath()) == "["){
            //run test command
            bool fileFound  = runTestCmd(cmd);
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
            return 0;
        }

        child_pid = fork();

        if(child_pid == 0){//fork() returns 0 to the child process
            execvp(cmd->getPath(), cmd->getArgs());


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

    return 0;
}

int Executor::getLastChildStatus(){
    return child_status;
}

bool Executor::runTestCmd(Command* cmd){
    std::vector<char*> testvec = cmd->getRawCmd();
    Parser subParser = Parser("null");
    struct stat sb;
    std::string fullArgString = testvec.at(1);
    std::string testFlag = "-e";
    char* testArgs;
    int backPos = fullArgString.length() - 1;
    
    if(std::string(cmd->getPath()) == "["){
        
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

void Executor::inOrder(Node* cmndNode){
    if(cmndNode == NULL || exitflag){
        return;
    }

    inOrder(cmndNode->left);

    if(cmndNode->cmd->cmdString() != "cmd"){
        if(cmndNode->cmd->cmdString() == "&&"){
            andflag = true;
        }else if(cmndNode->cmd->cmdString() == "||"){
            orflag = true;
        }else if(cmndNode->cmd->cmdString() == "exit"){
            exitflag = true;
            return;
        }else{
            //
        }
    }else{
        runCmds(cmndNode->cmd);
    }

    if(andflag && child_status != 0){
        andflag = false;
        return;
    }else if(orflag && child_status == 0){
        orflag = false;
        return;
    }else{
        inOrder(cmndNode->right);
    }
}

bool Executor::isExit(){
    return exitflag;
}
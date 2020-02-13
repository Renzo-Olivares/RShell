#include "../header/Executor.hpp"

Executor::Executor(CommandQueue* cmdQueue){
    cmdList = cmdQueue;
}

int Executor::runCmds(){
    while(!cmdList->isEmpty()){
        pid_t child_pid; 
        pid_t wait_child; //pid returned by waitpid

        if (cmdList->cmdString() != "cmd"){
            if(cmdList->cmdString() == "&&"){
                //std::cout << "AND Connector" << std::endl;
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
        }

        child_pid = fork();

        if(child_pid == 0){//fork() returns 0 to the child process
            execvp(cmdList->getPath(), cmdList->getArgs());


            //if child process reaches here execvp must have failed
            exit(1);
        }
        else{//fork() returns process id of child process
            if(child_pid == (pid_t)(-1)){
                exit(1);
            }else{
                wait_child = waitpid(child_pid,&child_status,0);
                //std::cout << "Parent: Child PID and exit status " << wait_child << " " << child_status << std::endl;
                if(child_status != 0){
                    perror("Command failed to execute!");
                }
            }
        }
        cmdList->popCmd();
    }
    return 0;
}

int Executor::getLastChildStatus(){
    return child_status;
}
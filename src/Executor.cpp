#include "../header/Executor.hpp"

Executor::Executor(std::queue<Command*> cmdQueue){
    commandQueue = cmdQueue;
}

int Executor::runCmds(){
    while(!commandQueue.empty()){
        pid_t child_pid; 
        pid_t wait_child; //pid returned by waitpid

        Command* currentCmd = commandQueue.front();

        if (currentCmd->cmdString() != "cmd"){
            if(currentCmd->cmdString() == "&&"){
                //std::cout << "AND Connector" << std::endl;
                if(child_status == 0){
                    commandQueue.pop(); //pop connector
                    continue;
                }else{
                    commandQueue.pop(); //pop connector
                    commandQueue.pop(); //pop next command
                    continue;
                }
            }else if(currentCmd->cmdString() == "||"){
                if(child_status != 0){ //last command was not successful
                    commandQueue.pop(); //pop connector
                    continue;
                }else{ //last command was successful
                    commandQueue.pop(); //pop connector
                    commandQueue.pop(); //pop next command
                    continue;
                }
            }else if(currentCmd->cmdString() == "exit"){
                //break everythig and return immediately
                std::queue<Command*> empty;
                std::swap(commandQueue, empty);
                return -1;
            }else{
                commandQueue.pop(); //pop connector
                continue;
            }
        }

        child_pid = fork();

        if(child_pid == 0){//fork() returns 0 to the child process
            execvp(currentCmd->getPath(), currentCmd->getArgs());


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
        commandQueue.pop();
    }
    return 0;
}
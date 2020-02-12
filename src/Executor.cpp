#include "../header/Executor.hpp"

Executor::Executor(std::queue<Command*> cmdQueue){
    commandQueue = cmdQueue;
}

void Executor::runCmds(){
    std::cout << "Running command queue" << std::endl;
    while(!commandQueue.empty()){
        pid_t child_pid; 
        pid_t wait_child; //pid returned by waitpid

        Command* currentCmd = commandQueue.front();

        if (currentCmd->cmdString() != "cmd"){
            if(currentCmd->cmdString() == "&&"){
                std::cout << "AND Connector" << std::endl;
                if(child_status == 0){
                    commandQueue.pop(); //pop connector
                    continue;
                }else{
                    commandQueue.pop(); //pop connector
                    commandQueue.pop(); //pop next command
                    continue;
                }
            }else if(currentCmd->cmdString() == "||"){
                std::cout << "OR Connector" << std::endl;
                if(child_status != 0){ //last command was not successful
                    commandQueue.pop(); //pop connector
                    continue;
                }else{ //last command was successful
                    commandQueue.pop(); //pop connector
                    commandQueue.pop(); //pop next command
                    continue;
                }
            }else{
                std::cout << "SemiColon/Blank Connector" << std::endl;
                commandQueue.pop(); //pop connector
                continue;
            }
        }

        std::cout << "Parent: Creating child process" << std::endl;
        child_pid = fork();

        if(child_pid == 0){//fork() returns 0 to the child process
            std::cout << "Child: Inside child process" << std::endl;
            std::cout << "Child: Child PID = " << getpid() << std::endl;
            std::cout << "Child: Running execvp()" << std::endl;
            execvp(currentCmd->getPath(), currentCmd->getArgs());


            //if child process reaches here execvp must have failed
            std::cout << "Child: execvp failed" << std::endl;
            exit(1);
        }
        else{//fork() returns process id of child process
            std::cout << "Parent: Inside parent process" << std::endl;
            if(child_pid == (pid_t)(-1)){
                std::cout << "Parent: fork failed to create Child process" << std::endl;
                exit(1);
            }else{
                std::cout << "Parent: waiting for Child to exit" << std::endl;
                wait_child = waitpid(child_pid,&child_status,0);
                std::cout << "Parent: Child PID and exit status " << wait_child << " " << child_status << std::endl;
            }
        }
        std::cout << "Executed command" << std::endl;
        commandQueue.pop();
    }
}
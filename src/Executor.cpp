#include "../header/Executor.hpp"

Executor::Executor(std::queue<Command*> cmdQueue){
    commandQueue = cmdQueue;
}

void Executor::runCmds(){
    std::cout << "Running command queue" << std::endl;
    while(!commandQueue.empty()){
        pid_t child_pid; 
        int child_status; //child exit status
        pid_t wait_child; //pid returned by waitpid

        Command* currentCmd = commandQueue.front();

        char allFlag[1] = {'a'};
        char *const flags[2] = {allFlag};
        char *const *lsArgs = flags;

        std::cout << "current command " << currentCmd->cmdString() << std::endl;
        std::cout << "current args " << *((*currentCmd).getArgs()) << std::endl;
        std::cout << "correct args " << **lsArgs << std::endl;

        std::cout << "Creating child process" << std::endl;
        child_pid = fork();

        if(child_pid == 0){//fork() returns 0 to the child process
            std::cout << "Inside child process" << std::endl;
            std::cout << "Child process: Child PID = " << getpid() << std::endl;
            std::cout << "Running execvp()" << std::endl;
            execvp(currentCmd->getPath(), currentCmd->getArgs());
            //execvp(currentCmd->getPath(), lsArgs);
            //if child process reaches here execvp must have failed
            std::cout << "Child process: execvp failed" << std::endl;
            exit(1);
        }
        else{//fork() returns process id of child process
            std::cout << "Inside parent process" << std::endl;
            if(child_pid == (pid_t)(-1)){
                std::cout << "Parent process: fork failed to create Child process" << std::endl;
                exit(1);
            }else{
                std::cout << "Parent process: waiting for Child to exit" << std::endl;
                wait_child = waitpid(child_pid,&child_status,0);
                std::cout << "Parent process: Child PID and exit status " << wait_child << " " << child_status << std::endl;
            }
        }
        std::cout << "Executed command" << std::endl;
        commandQueue.pop();
    }
}

/*
int Executor::newChild(){
    return 1;
}

void Executor::pauseParent(){

}
*/
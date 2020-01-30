#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

void execute(const char *exec, char *const argv[]){
    execvp(exec, argv);
}

int main(){
    char cmndLs[2] = {'l','s'};//change this to invalid command such as 'l', 'x' to test for failure
    const char *lsCmd = cmndLs;

    char allFlag[1] = {'a'};
    char *const flags[2] = {allFlag};
    char *const *lsArgs = flags;

    std::cout << "Setting up arguments for execvp ls -a" << std::endl;

    pid_t child_pid; 
    int child_status; //child exit status
    pid_t wait_child; //pid returned by waitpid

    std::cout << "Creating child process" << std::endl;
    child_pid = fork();

    //if child process 
    if(child_pid == 0){
        std::cout << "Inside child process" << std::endl;
        std::cout << "Child process: Child PID = " << getpid() << std::endl;
        execvp(lsCmd,lsArgs);

        //if child process reaches here execvp must have failed
        std::cout << "Child process: execvp failed" << std::endl;
        exit(1);
    }
    //if parent process
    else{
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

    return 0;
}

//fork() is called and attempts to create a child thread
//if fork fails to create child process then prints out fork failure and exits
//if fork succesfully creates child process then go to child process
//in child process print pid and run execvp
//if child process reaches exit(1) before it returns to parent process then execvp failed
//if execvp succesfully executes then return to parent process
//at parent process go into else block
//if child creation was succesfull then print the child pid and its exit status
//return of 256 actually means return of 1 means error, multiplies exit by 256
//return of 0 means succesfull
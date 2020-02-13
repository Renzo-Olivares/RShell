#include "../header/CommandQueue.hpp"

char* CommandQueue::getPath(){
    return (commandList.front())->getPath();
}

char** CommandQueue::getArgs(){
    return (commandList.front())->getArgs();
}

void CommandQueue::addQueue(std::queue<Command*> cmdQ){
    while(!cmdQ.empty()){
        addCmd(cmdQ.front());
        cmdQ.pop();
    }
}

void CommandQueue::addCmd(Command* command){
    commandList.push(command);
}

void CommandQueue::popCmd(){
    commandList.pop();
}

bool CommandQueue::isEmpty(){
    return commandList.empty();
}

std::string CommandQueue::cmdString(){
    return (commandList.front())->cmdString();
}
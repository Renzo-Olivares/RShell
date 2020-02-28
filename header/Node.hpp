#ifndef NODE_HPP
#define NODE_HPP

#include "../header/Command.hpp"

struct Node{
    Command* cmd;

    struct Node* left, *right;                   

    Node(Command* cmd){
        this->cmd = cmd;
        left = right = NULL;
    }
};

#endif /* NODE_HPP */
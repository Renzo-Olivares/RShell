#ifndef PARSER_HPP
#define PARSER_HPP

#include "../header/CommandQueue.hpp"
#include "../header/BasicCommand.hpp"
#include "../header/Connector.hpp"
#include "../header/ExitCommand.hpp"

#include <queue>
#include <regex>
#include <algorithm>
#include <vector>
#include <stack>
#include <boost/regex.hpp>
#include <boost/algorithm/string/trim.hpp>

struct Node{
    Command* cmd;

    struct Node* left, *right;                   

    Node(Command* cmd){
        this->cmd = cmd;
        left = right = NULL;
    }
};

class Parser{
    private:
        std::queue<Command*> parsedCmds;
        std::string userInput;
        struct Node* root;
    public:
        Parser(std::string rawUserInput);
        void run();
        std::queue<Command*> getParsedCmds();
        char* characterize(std::string rawString);
        void buildCmd(char* execu, char* args);
        std::string commentTrim(std::string rawInput);
        std::string whitespaceTrimLt(std::string rawString);
        char* addTwoChars(char* A, char* B);
        std::string popQuotes(std::string qString);
        std::queue<Command*> mirror(std::queue<Command*> cmdQ);
        std::queue<Command*> shuntingYard(std::queue<Command*> preSyQueue);
        void inOrder(struct Node* node, Command* inorderQueue);
        Command* buildTree(std::queue<Command*> outQueue);
        void buildPrescedenceQueue();
        void renzoYard();
};

#endif /* PARSER_HPP */
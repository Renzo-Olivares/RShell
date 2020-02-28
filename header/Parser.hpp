#ifndef PARSER_HPP
#define PARSER_HPP

#include "../header/BasicCommand.hpp"
#include "../header/Connector.hpp"
#include "../header/ExitCommand.hpp"
#include "../header/Node.hpp"

#include <iostream>
#include <queue>
#include <regex>
#include <algorithm>
#include <vector>
#include <stack>
#include <boost/regex.hpp>
#include <boost/algorithm/string/trim.hpp>

class Parser{
    private:
        std::queue<Command*> parsedCmds;
        std::string userInput;
        Node* cmndTree;
    public:
        Parser(std::string rawUserInput);
        void run();
        char* characterize(std::string rawString);
        void buildCmd(char* execu, char* args);
        std::string commentTrim(std::string rawInput);
        std::string whitespaceTrimLt(std::string rawString);
        char* addTwoChars(char* A, char* B);
        std::string popQuotes(std::string qString);
        std::queue<Command*> mirror(std::queue<Command*> cmdQ);
        std::queue<Command*> shuntingYard(std::queue<Command*> preSyQueue);
        void buildTree(std::queue<Command*> outQueue);
        void buildPrescedenceQueue();
        Node* getParsedCmndTree();
};

#endif /* PARSER_HPP */
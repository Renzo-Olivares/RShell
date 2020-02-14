#ifndef PARSER_HPP
#define PARSER_HPP

#include "../header/BasicCommand.hpp"
#include "../header/Connector.hpp"
#include "../header/ExitCommand.hpp"

#include <iostream>
#include <queue>
#include <regex>
#include <boost/regex.hpp>
#include <boost/algorithm/string/trim.hpp>

class Parser{
    private:
        std::queue<Command*> parsedCmds;
        std::string userInput;
    public:
        Parser(std::string rawUserInput);
        void run();
        std::queue<Command*> getParsedCmds();
        char* whitespaceTrimLt(std::string rawString);
        void buildCmd(char* execu, char* args);
        std::string commentTrim(std::string rawInput);
};

#endif /* PARSER_HPP */
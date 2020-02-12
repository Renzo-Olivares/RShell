#ifndef PARSER_HPP
#define PARSER_HPP

#include "../header/BasicCommand.hpp"
#include "../header/Connector.hpp"

#include <iostream>
#include <queue>
#include <boost/regex.hpp>
#include <boost/algorithm/string/trim.hpp>

class Parser{
    private:
        std::queue<Command*> parsedCmds;
    public:
        Parser();
        void run();
        std::queue<Command*> getParsedCmds();
        char* whitespaceTrimLt(std::string rawString);
};

#endif /* PARSER_HPP */
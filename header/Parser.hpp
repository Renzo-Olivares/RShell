#ifndef PARSER_HPP
#define PARSER_HPP

#include "../header/CommandQueue.hpp"
#include "../header/BasicCommand.hpp"
#include "../header/Connector.hpp"
#include "../header/ExitCommand.hpp"

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
        char* characterize(std::string rawString);
        void buildCmd(char* execu, char* args);
        std::string commentTrim(std::string rawInput);
        std::string whitespaceTrimLt(std::string rawString);
        char* addTwoChars(char* A, char* B);
        std::string popQuotes(std::string qString);
};

#endif /* PARSER_HPP */
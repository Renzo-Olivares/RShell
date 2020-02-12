#include "../header/Parser.hpp"

Parser::Parser(std::string rawUserInput){
    userInput = rawUserInput;
}

void Parser::run(){
    boost::regex re("(^&&|^\\|\\||^;|^\\s+)?(?<executable>\\w+)(?<arguments>\\s+[\"']?\\w+[\"']?)?\\s?+(?<connector>&&|\\|\\||;)?"); 
    boost::sregex_iterator iter(userInput.begin(), userInput.end(), re);
    boost::sregex_iterator end;

    for( ; iter != end; ++iter ) {
        char* full = whitespaceTrimLt((*iter)[0]);
        char* executable = whitespaceTrimLt((*iter)[2]);
        char* arguments = whitespaceTrimLt((*iter)[3]);
        char* connector = whitespaceTrimLt((*iter)[4]);

        Command* newCmd;
        Command* newConnector =  new Connector(connector);

        if(std::string(executable) == "exit"){
            newCmd = new ExitCommand(executable);
        }else{
            newCmd = new BasicCommand(executable, arguments);
        }

        parsedCmds.push(newCmd);
        parsedCmds.push(newConnector);
    }
}

std::queue<Command*> Parser::getParsedCmds(){
    return parsedCmds;
}

char* Parser::whitespaceTrimLt(std::string rawString){
    boost::algorithm::trim(rawString);
    int n = rawString.size();
    char* outp = new char[n + 1];
    std::copy(rawString.begin(), rawString.end(), outp);
    outp[n] = '\0';
    return outp;
}
/*
type Parser::commentTrim(){
    return trimmedstring
    //trim the hashtag(not inside quotes) and everything after it
}
*/
#include "../header/Parser.hpp"

Parser::Parser(std::string rawUserInput){
    userInput = rawUserInput;
}

void Parser::run(){
    //std::string sp("echo hello && echo goodbye ; mkdir \"bye\" &&echo             'lol' ||     echo fail ; echo 123; rshell"); 
    //std::string sp("echa A && echo B");
    boost::regex re("(^&&|^\\|\\||^;|^\\s+)?(?<executable>\\w+)(?<arguments>\\s+[\"']?\\w+[\"']?)?\\s?+(?<connector>&&|\\|\\||;)?"); 
    boost::sregex_iterator iter(userInput.begin(), userInput.end(), re);
    boost::sregex_iterator end;

    for( ; iter != end; ++iter ) {
        char* full = whitespaceTrimLt((*iter)[0]);
        char* executable = whitespaceTrimLt((*iter)[2]);
        char* arguments = whitespaceTrimLt((*iter)[3]);
        char* connector = whitespaceTrimLt((*iter)[4]);

        Command* newCmd = new BasicCommand(executable, arguments);
        Command* newConnector = new Connector(connector);
        std::cout << "Path: " << newCmd->getPath() << std::endl;
        std::cout << "Args: " << newCmd->getArgs() << std::endl;
        std::cout << "Connector: " << newConnector->cmdString() << std::endl;
        parsedCmds.push(newCmd);
        parsedCmds.push(newConnector);
        //push command into vector, then connector
        /*
        std::cout << "full command: " << full << '\n';
        std::cout << "executable: " << executable << '\n';
        std::cout << "arguments: " << arguments <<'\n';
        std::cout << "connector: " << connector <<'\n';
        std::cout << std::endl;
        */
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

//boost::regex connre("(?<Connector>(&&|\\|\\||;)(?=[^(\"|')]*(?:[(\"|')][^(\"|')]*[(\"|')][^(\"|')]*)*$))");
//boost::regex fullre("(?<fullcommand>(^&&|^\\|\\||^;|^\\s+)?(?<executable>\\w+)(?<arguments>\\s+[\"']?\\w+[\"']?)?\\s?+(?<connector>&&|\\|\\||;)?)");
//(?<Connector>(&&|\|\||;)(?=[^("|')]*(?:[("|')][^("|')]*[("|')][^("|')]*)*$)) 
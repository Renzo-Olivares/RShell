#include "../header/Parser.hpp"

Parser::Parser(){
}
void Parser::run(){
    std::string sp("echo hello && echo goodbye ; mkdir \"bye\" &&echo             'lol' ||     echo fail ; echo 123; rshell"); 
    boost::regex re("(^&&|^\\|\\||^;|^\\s+)?(?<executable>\\w+)(?<arguments>\\s+[\"']?\\w+[\"']?)?\\s?+(?<connector>&&|\\|\\||;)?"); 
    boost::sregex_iterator iter(sp.begin(), sp.end(), re);
    boost::sregex_iterator end;

    for( ; iter != end; ++iter ) {
        /*
        char* full = trim((*iter)[0]);
        char* executable = trim((*iter)[2]);
        char* arguments = trim((*iter)[3]);
        char* connector = trim((*iter)[4]);
        Command* newCmd = new BasicCommand(executable, arguments);
        Command* newConnector = new Connector(connector);
        //push command into vector, then connector
        */
        std::cout << "full command: " << (*iter)[0] << '\n';
        std::cout << "executable: " << (*iter)[2] << '\n';
        std::cout << "arguments: " << (*iter)[3] <<'\n';
        std::cout << "connector: " << (*iter)[4] <<'\n';
        std::cout << std::endl;
    }
    //return command vector
}

/*
type Parser::whitespaceTrim(){
    return trimmedstring
    //trim leading and trailing whitespaces
}

type Parser::commentTrim(){
    return trimmedstring
    //trim the hashtag(not inside quotes) and everything after it
}
*/

//boost::regex connre("(?<Connector>(&&|\\|\\||;)(?=[^(\"|')]*(?:[(\"|')][^(\"|')]*[(\"|')][^(\"|')]*)*$))");
//boost::regex fullre("(?<fullcommand>(^&&|^\\|\\||^;|^\\s+)?(?<executable>\\w+)(?<arguments>\\s+[\"']?\\w+[\"']?)?\\s?+(?<connector>&&|\\|\\||;)?)");
//(?<Connector>(&&|\|\||;)(?=[^("|')]*(?:[("|')][^("|')]*[("|')][^("|')]*)*$)) 
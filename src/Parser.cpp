#include "../header/Parser.hpp"

Parser::Parser(std::string rawUserInput){
    userInput = rawUserInput;
}

void Parser::run(){
    boost::regex re("[^\\s'\"]+|\"([^'\"]*)\"|'([^'\"]*)'"); 
    auto input_begin = boost::sregex_iterator(userInput.begin(), userInput.end(), re);
    auto input_end = boost::sregex_iterator();
    int tokencount = 1;
    int position = 1;
    int nummatches = std::distance(input_begin, input_end);
    char* exec;
    char* args;
    char* connector;

    for( ; input_begin != input_end; ++input_begin ) {
       char* token = whitespaceTrimLt((*input_begin)[0]);
       if(tokencount == 1){
           exec = whitespaceTrimLt((*input_begin)[0]);
           if(position == nummatches){
               //build and push
               buildCmd(exec, args);
               break;
           }
       }else if(tokencount == 2){
           args = whitespaceTrimLt((*input_begin)[0]);
           if(position == nummatches){
               //build and push
               buildCmd(exec, args);
               break;
           }
       }else if(tokencount == 3){
           connector = whitespaceTrimLt((*input_begin)[0]);
       }
       if(tokencount < 3){ //next token
           tokencount++;
       }else{
           //create command and connector, push onto queue
            Command* newCmd;
            if(std::string(exec) == "exit"){
                newCmd = new ExitCommand(exec);
            }else{
                newCmd = new BasicCommand(exec, args);
            }
            Command* newConnector =  new Connector(connector);
            parsedCmds.push(newCmd);
            parsedCmds.push(newConnector);
            tokencount = 1; //reset token count after connector
       }
       position++;
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

void Parser::buildCmd(char* execu, char* args){
    Command* newCmd;
    if(std::string(execu) == "exit"){
        newCmd = new ExitCommand(execu);
    }else{
        newCmd = new BasicCommand(execu, args);
    }
    parsedCmds.push(newCmd);
}
/*
type Parser::commentTrim(){
    return trimmedstring
    //trim the hashtag(not inside quotes) and everything after it
}
*/
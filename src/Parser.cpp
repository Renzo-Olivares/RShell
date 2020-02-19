#include "../header/Parser.hpp"

Parser::Parser(std::string rawUserInput){
    userInput = rawUserInput;
}

void Parser::run(){
    boost::regex re("[^\\s'\"]+|\"([^'\"]*)\"|'([^'\"]*)'");
    std::string cleanInput = commentTrim(userInput);
    std::string argstring = "";
    auto input_begin = boost::sregex_iterator(cleanInput.begin(), cleanInput.end(), re);
    auto input_end = boost::sregex_iterator();
    int tokencount = 1;
    int position = 1;
    int nummatches = std::distance(input_begin, input_end);
    char* exec;
    char* args;
    char* connector;
    bool semi = false;

    for( ; input_begin != input_end; ++input_begin ) {
       char* token = characterize(whitespaceTrimLt((*input_begin)[0]));
       if(tokencount == 1){
           args = NULL;
           exec = token;
           std::string execstring = std::string(exec);

           if(position == nummatches){
               //build and push
               buildCmd(exec, args);
               break;
           }
       }else if((*input_begin)[0] == "&&" || (*input_begin)[0] == "||" || (*input_begin)[0] == ";"){
           connector = token;
           buildCmd(exec, args);
           if(position != nummatches){
                buildCmd(connector, args);
           }
       }else if(tokencount > 1){
            if (tokencount  == 2){
                args = token;
            }else{
                char* blank = " ";
                args = addTwoChars(args, blank);
                args = addTwoChars(args, token);
            }
               std::string argstring = whitespaceTrimLt(std::string(args));
           if(argstring.at(argstring.length() - 1) == ';'){
               argstring.pop_back();

               buildCmd(exec,characterize(argstring));
               buildCmd(characterize(";"), args);
               
               semi = true;
           }
            if(position == nummatches){
               //build and push
               buildCmd(exec, args);
               break;
           }            
       }
       if((*input_begin)[0] == "&&" || (*input_begin)[0] == "||" || (*input_begin)[0] == ";" || semi){
           tokencount = 1;
           semi = false;
       }else if(tokencount < 3){ //next token
           tokencount++;
       }
       position++;
    }
}

std::queue<Command*> Parser::getParsedCmds(){
    return parsedCmds;
}

char* Parser::addTwoChars(char* A, char* B){
    char* newChar = (char*) malloc(1 + strlen(A) + strlen(B));
    strcpy(newChar, A);
    strcat(newChar, B);
    return newChar;
}

char* Parser::characterize(std::string rawString){
    int n = rawString.size();
    char* outp = new char[n + 1];
    std::copy(rawString.begin(), rawString.end(), outp);
    outp[n] = '\0';
    return outp;
}

std::string Parser::whitespaceTrimLt(std::string rawString){
    return boost::algorithm::trim_copy(rawString);
}

void Parser::buildCmd(char* execu, char* args){
    Command* newCmd;
    if(std::string(execu) == "exit"){
        newCmd = new ExitCommand(execu);
    }else if(std::string(execu) == "&&" || std::string(execu) == "||" || std::string(execu) == ";"){
        newCmd = new Connector(execu);
    }
    else{
        newCmd = new BasicCommand(execu, args);
    }
    parsedCmds.push(newCmd);
}

std::string Parser::commentTrim(std::string rawInput){
    std::regex re("#(?=[^(\"|')]*(?:[(\"|')][^(\"|')]*[(\"|')][^(\"|')]*)*$)");
    std::smatch m;
    std::regex_search(rawInput, m, re);
    return rawInput.substr(0, m.position(0));
}

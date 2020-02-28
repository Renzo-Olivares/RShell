#include "../header/Parser.hpp"
#include <iostream>

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
            //Hehe you can do it budddddyy
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

    buildPrescedenceQueue();
    std::queue<Command*> mirrorQueue = mirror(parsedCmds);
    std::queue<Command*> shyardQueue = shuntingYard(mirrorQueue);
    buildTree(shyardQueue);
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

std::string Parser::popQuotes(std::string qString){
    std::string qlessString;

    if(qString.at(0) == '"'){
        if(qString.at(qString.length() - 1) == '"'){
            qlessString = qString.substr(1,qString.length() - 2);
        }else{
            return qString; //no matching quotes return original
        }
    }else if(qString.at(0) == '\''){
        if(qString.at(qString.length() - 1) == '\''){
            qlessString = qString.substr(1,qString.length() - 2);
        }else{
            return qString; //no matching quotes return original
        }
    }else{
        return qString;
    }

    return whitespaceTrimLt(qlessString);
}

std::queue<Command*> Parser::mirror(std::queue<Command*> cmdQ){
    std::queue<Command*> reversedQueue;
    std::vector<Command*> origVect;

    while(!cmdQ.empty()){
        origVect.push_back(cmdQ.front());
        cmdQ.pop();
    }

    std::reverse(origVect.begin(), origVect.end());

    for(auto cmd: origVect){
        if(cmd->cmdString() == "("){
            cmd = new Connector(")");
        }else if(cmd->cmdString() == ")"){
            cmd = new Connector("(");
        }
        reversedQueue.push(cmd);
    }

    return reversedQueue;
}

std::queue<Command*> Parser::shuntingYard(std::queue<Command*> preSyQueue){
    std::stack<Command*> operatorStack;
    std::queue<Command*> outputQueue;

    while(!preSyQueue.empty()){

        Command* currCmd = preSyQueue.front();
        std::string token = currCmd->cmdString();

        if(token == "cmd" || token == "exit"){
            outputQueue.push(currCmd);
        }else if(token == "&&" || token == "||" || token == ";"){
            operatorStack.push(currCmd);
        }else if(token == "("){
            operatorStack.push(currCmd);
        }else if(token == ")"){

            while(!operatorStack.empty() && (operatorStack.top())->cmdString() != "("){
                outputQueue.push(operatorStack.top());
                operatorStack.pop();
            }

            if(operatorStack.empty()){
                //there is mismatched parentheses
            }

            if((operatorStack.top())->cmdString() == "("){
                operatorStack.pop();
            }
        }
        preSyQueue.pop();
    }

    //if operator stack not null pop 
    while(!operatorStack.empty()){
        if((operatorStack.top())->cmdString() == "(" || (operatorStack.top())->cmdString() == ")"){
            //if there is a parentheses at the top of the stack then there is mismatched parentheses
        }
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
    }

    return outputQueue;
}

void Parser::buildTree(std::queue<Command*> outQueue){
    std::stack<Node*> operandStack;

    while(!outQueue.empty()){
        if(outQueue.front()->cmdString() == "cmd" || outQueue.front()->cmdString() == "exit"){
            operandStack.push(new Node(outQueue.front()));
        }else{
            Node* opr1 = new Node(outQueue.front());
            Node* t1;
            Node* t2;

            t1 = operandStack.top();
            operandStack.pop();

            t2 = operandStack.top();
            operandStack.pop();
            
            opr1->right = t2;
            opr1->left = t1; 

            operandStack.push(opr1);
        }
        outQueue.pop();
    }

    cmndTree = operandStack.top();
}

void Parser::buildPrescedenceQueue(){
    std::queue<Command*> prescQueue;

    while(!parsedCmds.empty()){
        Command* currentCmd = parsedCmds.front();
        if(currentCmd->cmdString() == "cmd"){
            std::string cleanexec;
            std::string cleanargs;
            std::string execstring = currentCmd->getPath();
            std::vector<char*> rawCmd = currentCmd->getRawCmd();
            std::string argstring;
            if(rawCmd[1] != NULL){
                argstring = rawCmd[1];
            }
            int rightparCt = 0;
            bool parenstop = false;

            for(int i = 0; i < execstring.length(); i++){
                if(execstring[i] == '('){
                    Command* leftPar = new Connector("(");
                    prescQueue.push(leftPar);
                }else{
                    cleanexec += execstring[i];
                }
            }

            std::reverse(argstring.begin(), argstring.end());

            for(int i = 0; i < argstring.length(); i++){
                if(argstring[i] == ')' && !parenstop){
                    rightparCt++;
                }else{
                    parenstop = true;
                    cleanargs += argstring[i];
                }
            }

            //reverse cleanargs
            std::reverse(cleanargs.begin(), cleanargs.end());

            if(rawCmd[1] == NULL){
                prescQueue.push(new BasicCommand(characterize(cleanexec), NULL));                
            }else{
                prescQueue.push(new BasicCommand(characterize(cleanexec), characterize(cleanargs)));
            }

            for(int i = 0; i < rightparCt; i++){
                prescQueue.push(new Connector(")"));
            }
        }else{
            //if a connector just push it onto the queue
            prescQueue.push(currentCmd);
        }
        parsedCmds.pop();
    }
    std::swap(parsedCmds, prescQueue);
}

Node* Parser::getParsedCmndTree(){
    return cmndTree;
}
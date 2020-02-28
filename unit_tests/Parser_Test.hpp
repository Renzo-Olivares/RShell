#ifndef __PARSER_TEST_HPP__
#define __PARSER_TEST_HPP__

#include "gtest/gtest.h"
#include "../header/Parser.hpp"
#include "../header/Command.hpp"
#include "../header/BasicCommand.hpp"
#include "../header/Connector.hpp"
#include <iostream>
#include <string>
#include <queue>


TEST(ParserTest, WhiteSpaceTrim){
    std::string test = "     echo      ";
    Parser* analyzer = new Parser(test);
    EXPECT_EQ(analyzer->whitespaceTrimLt(test), "echo");
}

TEST(ParserTest, CommentTrim){
    std::string test = "echo hello# && echo goodbye";
    Parser* analyzer = new Parser(test);
    EXPECT_EQ(analyzer->commentTrim(test), "echo hello");
}

TEST(ParserTest, Characterize){
    std::string test = "echo hello";
    Parser* analyzer = new Parser(test);
    EXPECT_EQ(std::string(analyzer->characterize(test)), "echo hello");    
}

TEST(ParserTest, PopQuotesDouble){
    std::string test = "\"echo hello\"";
    Parser* analyzer = new Parser("null");
    EXPECT_EQ(analyzer->popQuotes(test), "echo hello");    
}

TEST(ParserTest, PopQuotesSingle){
    std::string test = "'echo hello'";
    Parser* analyzer = new Parser("null");
    EXPECT_EQ(analyzer->popQuotes(test), "echo hello");    
}

TEST(ParserTest, PopQuotesErrorSingle){
    std::string test = "'echo hello";
    Parser* analyzer = new Parser("null");
    EXPECT_EQ(analyzer->popQuotes(test), "'echo hello");    
}

TEST(ParserTest, PopQuotesErrorDouble){
    std::string test = "\"echo hello";
    Parser* analyzer = new Parser("null");
    EXPECT_EQ(analyzer->popQuotes(test), "\"echo hello");    
}

TEST(ParserTest, MirrorQueue){
    std::queue<Command*> cmdQ;
    char* exec = "echo";
    char* argsA = "A";
    char* argsB = "B";
    char* argsC = "C";
    char* argsD = "D";
    Command* lpar = new Connector("(");
    Command* acmd = new BasicCommand(exec, argsA);
    Command* andc = new Connector("&&");
    Command* bcmd = new BasicCommand(exec, argsB);
    Command* rpar = new Connector(")");
    Command* orc = new Connector("||");
    Command* ccmd = new BasicCommand(exec, argsC);
    Command* dcmd = new BasicCommand(exec, argsD);  

    cmdQ.push(lpar);
    cmdQ.push(acmd);
    cmdQ.push(andc);
    cmdQ.push(bcmd);
    cmdQ.push(rpar);
    cmdQ.push(orc);
    cmdQ.push(lpar);
    cmdQ.push(ccmd);
    cmdQ.push(andc);
    cmdQ.push(dcmd);
    cmdQ.push(rpar);

    std::string test = "\"echo hello";
    Parser* analyzer = new Parser("null");
    std::queue<Command*> newQ = analyzer->mirror(cmdQ);
    std::queue<Command*> syQ = analyzer->shuntingYard(newQ);

    analyzer->buildTree(syQ);
    //EXPECT_EQ(analyzer->popQuotes(test), "\"echo hello");    
}

TEST(ParserTest, PrescTest){
    std::string test = "((echo hello && echo world) || (echo goodbye && echo earth))";
    Parser* analyzer = new Parser(test);
    analyzer->run();
    //EXPECT_EQ(analyzer->popQuotes(test), "\"echo hello");    
}

#endif //__PARSER_TEST_HPP__

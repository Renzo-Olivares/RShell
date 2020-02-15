#ifndef __PARSER_TEST_HPP__
#define __PARSER_TEST_HPP__

#include "gtest/gtest.h"
#include "../header/Parser.hpp"
#include "../header/Command.hpp"
#include <iostream>
#include <string>


TEST(ParserTest, SimpleCmd){
    std::string testInput = "echo hello";
    Parser* analyzer = new Parser(testInput);
    analyzer->run();
    std::queue<Command*> parsedCmds = analyzer->getParsedCmds();
    Command* newCmd = parsedCmds.front();
	EXPECT_EQ(std::string(newCmd->getPath()), "echo");
	EXPECT_EQ(std::string((newCmd->getArgs())[1]), "hello");
}

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

#endif //__PARSER_TEST_HPP__

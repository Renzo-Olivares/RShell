#ifndef __PARSER_TEST_HPP__
#define __PARSER_TEST_HPP__

#include "gtest/gtest.h"
#include "../header/Parser.hpp"
#include "../header/Command.hpp"


TEST(ParserTest, SimpleCmd){
    std::string testInput = "echo hello";
    Parser* analyzer = new Parser(testInput);
    analyzer->run();
    std::queue<Command*> parsedCmds = analyzer->getParsedCmds();
    std::cout << (parsedCmds.front())->cmdString() << std::endl;
    Command* newCmd = parsedCmds.front();
	EXPECT_EQ(std::string(newCmd->getPath()), "echo");
	EXPECT_EQ(std::string((newCmd->getArgs())[1]), "hello");
}

TEST(ParserTest, WhiteSpaceTrim){
    std::string test = "     echo      ";
    Parser* analyzer = new Parser(test);
    char* clean  = analyzer->whitespaceTrimLt(test);
    EXPECT_EQ(std::string(clean), "echo");
}

TEST(ParserTest, CommentTrim){
    std::string test = "echo hello# && echo goodbye";
    Parser* analyzer = new Parser(test);
    EXPECT_EQ(analyzer->commentTrim(test), "echo hello");
}

#endif //__PARSER_TEST_HPP__

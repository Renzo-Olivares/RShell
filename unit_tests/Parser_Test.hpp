#ifndef __PARSER_TEST_HPP__
#define __PARSER_TEST_HPP__

#include "gtest/gtest.h"
#include "../header/Parser.hpp"
#include "../header/Command.hpp"
#include "../header/BasicCommand.hpp"
#include "../header/Connector.hpp"
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

#endif //__PARSER_TEST_HPP__

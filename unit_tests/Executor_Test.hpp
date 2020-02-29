#ifndef __EXECUTOR_TEST_HPP__
#define __EXECUTOR_TEST_HPP__

#include "gtest/gtest.h"
#include "../header/Executor.hpp"
#include "../header/Command.hpp"
#include "../header/ExitCommand.hpp"
#include "../header/Connector.hpp"
#include "../header/Parser.hpp"
#include "../header/Node.hpp"

TEST(ExecutorTest, ExitCmd){
    bool exitf = false;
    Parser testParse = Parser("exit");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor runner = Executor();
    runner.inOrder(cmndTree);
    exitf = runner.isExit()? true:false;

	EXPECT_EQ(exitf, true);
}

TEST(ExecutorTest, Success){
    bool exitf = false;
    Parser testParse = Parser("echo hello");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, true);
}


TEST(ExecutorTest, Flags){
    bool exitf = false;
    Parser testParse = Parser("ls -a");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, true);
}


TEST(ExecutorTest, AndConnector){
    bool exitf = false;
    Parser testParse = Parser("echo hello && echo goodbye");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, true);
}


TEST(ExecutorTest, AndConnectorFail){
    bool exitf = false;
    Parser testParse = Parser("echa hello && echo bye");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, false);
}


TEST(ExecutorTest, OrConnector){
    bool exitf = false;
    Parser testParse = Parser("echo hello || echo yessir");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, true);
}


TEST(ExecutorTest, SemiColConnector){
    bool exitf = false;
    Parser testParse = Parser("echo hello;echo goodbye");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, true);
}


TEST(ExecutorTest, Parentheses){
    bool exitf = false;
    Parser testParse = Parser("(echo a && echo b) || (echo c && echo d)");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, true);
}

TEST(ExecutorTest, Parentheses2){
    bool exitf = false;
    Parser testParse = Parser("(echo a && echo b) || echo c && echo d");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, true);
}


TEST(ExecutorTest, Parentheses3){
    bool exitf = false;
    Parser testParse = Parser("echo a && echo b || (echo c && echo d)");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, true);
}

TEST(ExecutorTest, LiteralTest){
    bool exitf = false;
    Parser testParse = Parser("test -e test");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, true);
}

TEST(ExecutorTest, LiteralFileTest){
    bool exitf = false;
    Parser testParse = Parser("test -f test");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, true);
}

TEST(ExecutorTest, LiteralDirectoryTest){
    bool exitf = false;
    Parser testParse = Parser("test -d unit_tests");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, true);
}

TEST(ExecutorTest, LiteralNoFlagTest){
    bool exitf = false;
    Parser testParse = Parser("test test");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, true);
}

TEST(ExecutorTest, LiteralDoubleQuotesTest){
    bool exitf = false;
    Parser testParse = Parser("test -e \"test\"");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, true);
}


TEST(ExecutorTest, LiteralSingleQuotesTest){
    bool exitf = false;
    Parser testParse = Parser("test -e 'test'");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, true);
}

TEST(ExecutorTest, SymbolicTest){
    bool exitf = false;
    Parser testParse = Parser("[ -e rshell ]");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, true);
}

TEST(ExecutorTest, SymbolicDoubleQuotesTest){
    bool exitf = false;
    Parser testParse = Parser("[ -e \"test\" ]");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, true);
}

TEST(ExecutorTest, SymbolicSingleQuotesTest){
    bool exitf = false;
    Parser testParse = Parser("[ -e 'rshell' ]");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, true);
}


TEST(ExecutorTest, SymbolicNoFlagTest){
    bool exitf = false;
    Parser testParse = Parser("[ rshell ]");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, true);
}


TEST(ExecutorTest, LiteralTestFail){
    bool exitf = false;
    Parser testParse = Parser("test -e notthere");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, false);
}

TEST(ExecutorTest, SymbolicTestBracketFail){
    bool exitf = false;
    Parser testParse = Parser("[ -e nothere ]");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, false);
}

TEST(ExecutorTest, SymbolicTestFail){
    bool exitf = false;
    Parser testParse = Parser("[ nothere ]");
    testParse.run();
    Node* cmndTree = testParse.getParsedCmndTree();
	Executor* runner = new Executor();
    runner->inOrder(cmndTree);
    exitf = runner->getLastChildStatus() == 0? true:false;

	EXPECT_EQ(exitf, false);
}

#endif //__EXECUTOR_TEST_HPP__

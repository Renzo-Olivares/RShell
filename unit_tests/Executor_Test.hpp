#ifndef __EXECUTOR_TEST_HPP__
#define __EXECUTOR_TEST_HPP__

#include "gtest/gtest.h"
#include "../header/Executor.hpp"
#include "../header/Command.hpp"
#include "../header/CommandQueue.hpp"
#include "../header/ExitCommand.hpp"
#include "../header/Connector.hpp"

TEST(ExecutorTest, ExitCmd){
    bool exitf = false;
	char* exits = "exit";
    CommandQueue* newQueue = new CommandQueue();
    Command* exitcmd = new ExitCommand(exits);
    newQueue->addCmd(exitcmd);
	Executor* runner = new Executor(newQueue);
    exitf = runner->runCmds() == 0? false:true;

	EXPECT_EQ(exitf, true);
}

TEST(ExecutorTest, Success){
    bool exitf = false;
	char* exec = "echo";
    char* args = "hello";
    CommandQueue* newQueue = new CommandQueue();
    Command* cmd = new BasicCommand(exec, args);
    newQueue->addCmd(cmd);
	Executor* runner = new Executor(newQueue);
    exitf = runner->runCmds() == 0? false:true;

	EXPECT_EQ(exitf, false);
}

TEST(ExecutorTest, Flags){
	char* exec = "ls";
    char* args = "-a";
    CommandQueue* newQueue = new CommandQueue();
    Command* cmd = new BasicCommand(exec, args);
    newQueue->addCmd(cmd);
	Executor* runner = new Executor(newQueue);
    runner->runCmds();

	EXPECT_EQ(runner->getLastChildStatus(), 0);
}

TEST(ExecutorTest, AndConnector){
	char* exec = "echo";
    char* args = "hello";
    char* argsb = "world";
    char* ands = "&&";
    CommandQueue* newQueue = new CommandQueue();
    Command* cmda = new BasicCommand(exec, args);
    Command* cmdb = new BasicCommand(exec, argsb);
    Command* andc = new Connector(ands);
    newQueue->addCmd(cmda);
    newQueue->addCmd(andc);
    newQueue->addCmd(cmdb);
	Executor* runner = new Executor(newQueue);
    runner->runCmds();

	EXPECT_EQ(runner->getLastChildStatus(), 0);
}

TEST(ExecutorTest, AndConnectorFail){
    bool exitf = false;
	char* execa = "echa";
    char* args = "hello";
    char* exec = "echo";
    char* ands = "&&";
    CommandQueue* newQueue = new CommandQueue();
    Command* cmda = new BasicCommand(execa, args);
    Command* cmdb = new BasicCommand(exec, args);
    Command* andc = new Connector(ands);
    newQueue->addCmd(cmda);
    newQueue->addCmd(andc);
    newQueue->addCmd(cmdb);
	Executor* runner = new Executor(newQueue);
    runner->runCmds();

	EXPECT_EQ(runner->getLastChildStatus(), 256);
}

TEST(ExecutorTest, OrConnector){
    bool exitf = false;
	char* exec = "echo";
    char* args = "hello";
    char* argsb = "world";
    char* ors = "||";
    CommandQueue* newQueue = new CommandQueue();
    Command* cmda = new BasicCommand(exec, args);
    Command* cmdb = new BasicCommand(exec, argsb);
    Command* orc = new Connector(ors);
    newQueue->addCmd(cmda);
    newQueue->addCmd(orc);
    newQueue->addCmd(cmdb);
	Executor* runner = new Executor(newQueue);
    runner->runCmds();

	EXPECT_EQ(runner->getLastChildStatus(), 0);
}

TEST(ExecutorTest, SemiColConnector){
    bool exitf = false;
	char* exec = "echo";
    char* args = "hello";
    char* argsb = "world";
    char* semis = ";";
    CommandQueue* newQueue = new CommandQueue();
    Command* cmda = new BasicCommand(exec, args);
    Command* cmdb = new BasicCommand(exec, argsb);
    Command* semic = new Connector(semis);
    newQueue->addCmd(cmda);
    newQueue->addCmd(semic);
    newQueue->addCmd(cmdb);
	Executor* runner = new Executor(newQueue);
    runner->runCmds();

	EXPECT_EQ(runner->getLastChildStatus(), 0);
}

#endif //__EXECUTOR_TEST_HPP__
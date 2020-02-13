#ifndef __COMMANDQUEUE_TEST_HPP__
#define __COMMANDQUEUE_TEST_HPP__

#include "gtest/gtest.h"
#include "../header/Command.hpp"
#include "../header/CommandQueue.hpp"
#include "../header/Connector.hpp"
#include "../header/ExitCommand.hpp"
#include "../header/BasicCommand.hpp"

TEST(CommandQueueTest, CQNotEmpty){
    char* exec = "echo";
    char* args = "hello";

	CommandQueue* cq = new CommandQueue();
    Command* bcmd = new BasicCommand(exec,args);
    cq->addCmd(bcmd);

	EXPECT_EQ(cq->isEmpty(), false);
}

TEST(CommandQueueTest, CQIsEmpty){
	CommandQueue* cq = new CommandQueue();

	EXPECT_EQ(cq->isEmpty(), true);
}

TEST(CommandQueueTest, CQClear){
    char* exec = "echo";
    char* args = "hello";

    CommandQueue* cq = new CommandQueue();
    Command* bcmd = new BasicCommand(exec,args);
    cq->addCmd(bcmd);
    cq->clear();

	EXPECT_EQ(cq->isEmpty(), true);
}

TEST(CommandQueueTest, CQAdd){
    char* exec = "echo";
    char* args = "hello";

	CommandQueue* cq = new CommandQueue();
    Command* bcmd = new BasicCommand(exec,args);
    cq->addCmd(bcmd);

	EXPECT_EQ(cq->isEmpty(), false);
}

TEST(CommandQueueTest, CQPop){
    char* exec = "echo";
    char* args = "hello";

	CommandQueue* cq = new CommandQueue();
    Command* bcmd = new BasicCommand(exec,args);
    cq->addCmd(bcmd);
    cq->popCmd();

	EXPECT_EQ(cq->isEmpty(), true);
}

TEST(CommandQueueTest, CQGetPathFront){
    char* exec = "echo";
    char* args = "hello";
	CommandQueue* cq = new CommandQueue();
    Command* bcmd = new BasicCommand(exec,args);
    cq->addCmd(bcmd);

	EXPECT_EQ(std::string(cq->getPath()), "echo");
}

/*
TEST(CommandQueueTest, CQGetArgsFront){
    char* exec = "echo";
    char* args = "hello";

	CommandQueue* cq = new CommandQueue();
    Command* bcmd = new BasicCommand(exec,args);
    cq->addCmd(bcmd);

	EXPECT_EQ(std::string((cq->getArgs)[1]), "hello");
}

TEST(CommandQueueTest, CQAddQueue){
    char* ors = "||";
	CommandQueue* cq = new CommandQueue();
    Command* orc = new Connector(ors);

	EXPECT_EQ(cq->cmdString(), "||");
}
*/

TEST(CommandQueueTest, CQCmdTypeOrc){
    char* ors = "||";
	CommandQueue* cq = new CommandQueue();
    Command* orc = new Connector(ors);
    cq->addCmd(orc);

	EXPECT_EQ(cq->cmdString(), "||");
}

TEST(CommandQueueTest, CQCmdTypeAndc){
    char* ands = "&&";
	CommandQueue* cq = new CommandQueue();
    Command* andc = new Connector(ands);
    cq->addCmd(andc);

	EXPECT_EQ(cq->cmdString(), "&&");
}


TEST(CommandQueueTest, CQCmdTypeSemiC){
    char* semis = ";";
	CommandQueue* cq = new CommandQueue();
    Command* semic = new Connector(semis);
    cq->addCmd(semic);

	EXPECT_EQ(cq->cmdString(), ";");
}


TEST(CommandQueueTest, CQCmdTypeBC){
    char* exec = "echo";
    char* args = "hello";

	CommandQueue* cq = new CommandQueue();
    Command* bcmd = new BasicCommand(exec,args);
    cq->addCmd(bcmd);

	EXPECT_EQ(cq->cmdString(), "cmd");
}


TEST(CommandQueueTest, CQCmdTypeNull){
    char* nulls = "";
	CommandQueue* cq = new CommandQueue();
    Command* nullc = new Connector(nulls);
    cq->addCmd(nullc);

	EXPECT_EQ(cq->cmdString(), "");
}

TEST(CommandQueueTest, CQExitCmd){
    char* exits = "exit";
	CommandQueue* cq = new CommandQueue();
    Command* exitcmd = new ExitCommand(exits);
    cq->addCmd(exitcmd);

	EXPECT_EQ(cq->cmdString(), "exit");
}

#endif //__COMMANDQUEUE_TEST_HPP__

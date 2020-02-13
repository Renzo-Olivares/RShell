#ifndef __BASICCOMMAND_TEST_HPP__
#define __BASICCOMMAND_TEST_HPP__

#include "gtest/gtest.h"
#include "../header/Command.hpp"
#include "../header/BasicCommand.hpp"

TEST(BasicCommandTest, BCPathTest){
	char* exec = "echo";
	char* args = "hello";

	Command* testcmd = new BasicCommand(exec,args);

	EXPECT_EQ(std::string(testcmd->getPath()), "echo");
}

TEST(BasicCommandTest, BCArgsTest){
	char* exec = "echo";
	char* args = "hello";
	
	Command* testcmd = new BasicCommand(exec,args);
	EXPECT_EQ(std::string(testcmd->getArgs()), "hello");
}

TEST(BasicCommandTest, BCcmdStringTest){

   	char* exec = "echo";
	char* args = "hello";
	
	Command* testcmd = new BasicCommand(exec,args);
	EXPECT_EQ(std::string(testcmd->cmdString()), "echo hello");
}

TEST(BasicCommandTest, BCechaTest){
	char* exec = "echa";
	char* args = "hello";
	
	Command* testcmd = new BasicCommand(exec,args);
	EXPECT_EQ(std::string(testcmd->getPath()), "echa");
}

#endif

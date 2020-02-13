#ifndef __BASICCOMMAND_TEST_HPP__
#define __BASICCOMMAND_TEST_HPP__

#include "gtest/gtest.h"
#include "../header/Command.hpp"
#include "../header/BasicCommand.hpp"

TEST(BasicCommandTest, BCPath){
	char* exec = "echo";
	char* args = "hello";

	Command* testcmd = new BasicCommand(exec,args);

	EXPECT_EQ(std::string(testcmd->getPath()), "echo");
}

TEST(BasicCommandTest, BCArgs){
	char* exec = "echo";
	char* args = "hello";
	
	Command* testcmd = new BasicCommand(exec,args);
	EXPECT_EQ(std::string((testcmd->getArgs())[1]), "hello");
}

TEST(BasicCommandTest, BCcmdString){

   	char* exec = "echo";
	char* args = "hello";
	
	Command* testcmd = new BasicCommand(exec,args);
	EXPECT_EQ(testcmd->cmdString(), "cmd");
}

TEST(BasicCommandTest, BCecha){
	char* exec = "echa";
	char* args = "hello";
	
	Command* testcmd = new BasicCommand(exec,args);
	EXPECT_EQ(std::string(testcmd->getPath()), "echa");
}

#endif //__BASICCOMMAND_TEST_HPP__

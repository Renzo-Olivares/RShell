#ifndef __EXITCOMMAND_TEST_HPP__
#define __EXITCOMMAND_TEST_HPP__

#include "gtest/gtest.h"
#include "../header/Command.hpp"
#include "../header/ExitCommand.hpp"

TEST(ExitCommandTest, BCPath){
	char* exits = "exit";
	Command* exitc = new ExitCommand(exits);

	EXPECT_EQ(exitc->cmdString(), "exit");
}

#endif //__EXITCOMMAND_TEST_HPP__

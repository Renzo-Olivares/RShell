#ifndef __CONNECTOR_TEST_HPP__
#define __CONNECTOR_TEST_HPP__

#include "gtest/gtest.h"
#include "../header/Command.hpp"
#include "../header/Connector.hpp"

TEST(ConnectorTest, AndConnector){
    char* andc = "&&";

	Command* testconn = new Connector(andc);

	EXPECT_EQ(testconn->cmdString(), "&&");
}

TEST(ConnectorTest, OrConnector){
	char* orc = "||";
	
	Command* testconn = new Connector(orc);
	EXPECT_EQ(testconn->cmdString(), "||");
}

TEST(ConnectorTest, SemiColonConnector){
   	char* semic = ";";
	
	Command* testconn = new Connector(semic);
	EXPECT_EQ(testconn->cmdString(), ";");
}

TEST(ConnectorTest, NullConnector){
	char* nullc = "";
	
	Command* testconn = new Connector(nullc);
	EXPECT_EQ(testconn->cmdString(), "");
}

#endif //__CONNECTOR_TEST_HPP__

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#Boost
FIND_PACKAGE(Boost COMPONENTS regex REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_BUILD_TYPE Debug)

ADD_EXECUTABLE(rshell
    src/main.cpp
    src/Command.cpp
    src/Executor.cpp
    src/BasicCommand.cpp
    src/Parser.cpp
    src/ShellClient.cpp
    src/Connector.cpp
    src/UserInput.cpp
    src/ExitCommand.cpp
    src/CommandQueue.cpp
)

#ADD_EXECUTABLE(test
#)

TARGET_LINK_LIBRARIES(
	rshell
	LINK_PUBLIC ${Boost_LIBRARIES}
)

#TARGET_LINK_LIBRARIES(test gtest)
#TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=0N)


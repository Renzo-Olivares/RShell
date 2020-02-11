CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_BUILD_TYPE Debug)

ADD_EXECUTABLE(rshell
    src/main.cpp
    src/Command.cpp
    src/Executor.cpp
    src/BasicCommand.cpp
)

#ADD_EXECUTABLE(test
#)

#TARGET_LINK_LIBRARIES(test gtest)
#TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=0N)
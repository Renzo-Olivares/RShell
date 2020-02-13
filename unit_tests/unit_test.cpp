#include "gtest/gtest.h"
#include "../unit_tests/BasicCommand_Test.hpp"
#include "../unit_tests/Connector_Test.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
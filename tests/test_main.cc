#include "syntax_core.hh"
#include "syntax_movements.hh"
#include "syntax_solver.hh"
#include "gtest/gtest.h"

// GTest main function
// runs the syntax tests

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

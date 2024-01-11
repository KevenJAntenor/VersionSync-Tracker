#include <gtest/gtest.h>

#include "utils.h"
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  fix_path();
  return RUN_ALL_TESTS();
}

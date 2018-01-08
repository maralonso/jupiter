#include "cu/cu.h"

  // Declarations of tests
  TEST(test_node_init);

  // Collect tests into test suite
  TEST_SUITE(generation) {
      TEST_ADD(test_node_init),
      TEST_SUITE_CLOSURE
  };

#include "cu/cu.h"

// Declarations of tests
TEST(test_move_init);
TEST(test_node_init_fail);
TEST(test_insert_move);
TEST(test_insert_move_fail);

// Collect tests into test suite
TEST_SUITE(generation) {
    TEST_ADD(test_move_init),
    TEST_ADD(test_node_init_fail),
    TEST_ADD(test_insert_move),
    TEST_ADD(test_insert_move_fail),
    TEST_SUITE_CLOSURE
};

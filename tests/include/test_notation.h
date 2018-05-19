#include "cu/cu.h"

TEST(test_get_notation);
TEST(get_move);

TEST_SUITE(notation) {
    TEST_ADD(test_get_notation),
    TEST_ADD(get_move),
    TEST_SUITE_CLOSURE
};

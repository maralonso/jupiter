#include "cu/cu.h"

TEST(test_rotate_0);
TEST(test_rotate_90);
TEST(test_rotate_180);
TEST(test_rotate_270);

TEST_SUITE(pieces) {
    TEST_ADD(test_rotate_0),
    TEST_ADD(test_rotate_90),
    TEST_ADD(test_rotate_180),
    TEST_ADD(test_rotate_270),
    TEST_SUITE_CLOSURE
};

#include "cu/cu.h"

TEST(test_rook_no_moves);
TEST(test_rook_moves_left);
TEST(test_rook_moves_right);
TEST(test_rook_moves_up);
TEST(test_rook_moves_down);
TEST(test_rook_takes);
TEST(test_rook_attak_square);

TEST_SUITE(rook_moves) {
    TEST_ADD(test_rook_no_moves),
    TEST_ADD(test_rook_moves_right),
    TEST_ADD(test_rook_moves_left),
    TEST_ADD(test_rook_moves_up),
    TEST_ADD(test_rook_moves_down),
    TEST_ADD(test_rook_takes),
    TEST_ADD(test_rook_attak_square),
    TEST_SUITE_CLOSURE
};

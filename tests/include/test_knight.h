#include "cu/cu.h"

TEST(test_knight_no_moves);
TEST(test_knight_moves_left_up);
TEST(test_knight_moves_left_down);
TEST(test_knight_moves_right_up);
TEST(test_knight_moves_right_down);
TEST(test_knight_takes);
TEST(test_knight_attak_square);

TEST_SUITE(knight_moves) {
    TEST_ADD(test_knight_no_moves),
    TEST_ADD(test_knight_moves_right_up),
    TEST_ADD(test_knight_moves_right_down),
    TEST_ADD(test_knight_moves_left_up),
    TEST_ADD(test_knight_moves_left_down),
    TEST_ADD(test_knight_takes),
    TEST_ADD(test_knight_attak_square),
    TEST_SUITE_CLOSURE
};



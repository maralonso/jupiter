#include "cu/cu.h"

TEST(test_bishop_no_moves);
TEST(test_bishop_moves_left_up);
TEST(test_bishop_moves_left_down);
TEST(test_bishop_moves_right_up);
TEST(test_bishop_moves_right_down);
TEST(test_bishop_takes);
TEST(test_bishop_attak_square);

TEST_SUITE(bishop_moves) {
    TEST_ADD(test_bishop_no_moves),
    TEST_ADD(test_bishop_moves_right_up),
    TEST_ADD(test_bishop_moves_right_down),
    TEST_ADD(test_bishop_moves_left_up),
    TEST_ADD(test_bishop_moves_left_down),
    TEST_ADD(test_bishop_takes),
    TEST_ADD(test_bishop_attak_square),
    TEST_SUITE_CLOSURE
};


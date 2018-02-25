#include "cu/cu.h"

TEST(test_king_no_moves);
TEST(test_king_moves_left_up);
TEST(test_king_moves_left_down);
TEST(test_king_moves_right_up);
TEST(test_king_moves_right_down);
TEST(test_king_takes);
TEST(test_king_short_castles);
TEST(test_king_long_castles);
TEST(test_king_no_castles);
TEST(test_king_no_castles2);

TEST_SUITE(king_moves) {
    TEST_ADD(test_king_no_moves),
    TEST_ADD(test_king_moves_right_up),
    TEST_ADD(test_king_moves_right_down),
    TEST_ADD(test_king_moves_left_up),
    TEST_ADD(test_king_moves_left_down),
    TEST_ADD(test_king_takes),
    TEST_ADD(test_king_short_castles),
    TEST_ADD(test_king_long_castles),
    TEST_ADD(test_king_no_castles),
    TEST_ADD(test_king_no_castles2),
    TEST_SUITE_CLOSURE
};

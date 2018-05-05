#include "cu/cu.h"

TEST(test_fen_get_board);
TEST(test_fen_get_board_moves);
TEST(test_fen_get_fen);

TEST_SUITE(fen_utils) {
    TEST_ADD(test_fen_get_board),
    TEST_ADD(test_fen_get_board_moves),
    TEST_ADD(test_fen_get_fen),
    TEST_SUITE_CLOSURE
};


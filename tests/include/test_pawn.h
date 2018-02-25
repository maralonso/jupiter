#include "cu/cu.h"

TEST(test_pawn_no_moves);
TEST(test_pawn_moves_fordward);
TEST(test_pawn_takes);
TEST(test_pawn_passant);
TEST(test_pawn_promote);
TEST(test_pawn_attak_square);

TEST_SUITE(pawn_moves) {
    TEST_ADD(test_pawn_no_moves),
    TEST_ADD(test_pawn_moves_fordward),
    TEST_ADD(test_pawn_takes),
    TEST_ADD(test_pawn_passant),
    TEST_ADD(test_pawn_promote),
    TEST_ADD(test_pawn_attak_square),
    TEST_SUITE_CLOSURE
};

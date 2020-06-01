#include "cu/cu.h"

TEST(test_move_init);
TEST(test_node_init_fail);
TEST(test_insert_move);
TEST(test_insert_move_fail);
TEST(test_square_attaked);
TEST(test_clear_castles);
TEST(test_gen_moves);
TEST(test_make_move);
TEST(test_make_move_castle);
TEST(test_make_move_passant);
TEST(test_passant_flag_is_set);
TEST(test_make_move_promotion);
TEST(test_perft_1);
TEST(test_perft_2);
TEST(test_perft_3);
TEST(test_perft_4);
TEST(test_perft_5);
TEST(test_perft_6);

TEST_SUITE(generation) {
    TEST_ADD(test_move_init),
    TEST_ADD(test_node_init_fail),
    TEST_ADD(test_insert_move),
    TEST_ADD(test_insert_move_fail),
    TEST_ADD(test_square_attaked),
    TEST_ADD(test_clear_castles),
    TEST_ADD(test_gen_moves),
    TEST_ADD(test_make_move),
    TEST_ADD(test_make_move_castle),
    TEST_ADD(test_make_move_passant),
    TEST_ADD(test_passant_flag_is_set),
    TEST_ADD(test_make_move_promotion),
    TEST_ADD(test_perft_1),
    TEST_ADD(test_perft_2),
    TEST_ADD(test_perft_3),
    TEST_ADD(test_perft_4),
    TEST_ADD(test_perft_5),
    TEST_ADD(test_perft_6),
    TEST_SUITE_CLOSURE
};

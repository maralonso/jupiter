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
TEST(test_make_move_promotion);

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
    TEST_ADD(test_make_move_promotion),
    TEST_SUITE_CLOSURE
};

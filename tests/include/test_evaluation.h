#include "cu/cu.h"

TEST(evaluation_material);
TEST(evaluation_rook_moves);
TEST(evaluation_bishop_moves);
TEST(evaluation_rook_doubled);
TEST(evaluation_rook_x_ray);
TEST(evaluation_bishop_unexpulsable);
TEST(evalution_bishop_x_ray);

TEST_SUITE(evaluation) {
    TEST_ADD(evaluation_material),
    TEST_ADD(evaluation_rook_moves),
    TEST_ADD(evaluation_bishop_moves),
    TEST_ADD(evaluation_rook_doubled),
    TEST_ADD(evaluation_rook_x_ray),
    TEST_ADD(evaluation_bishop_unexpulsable),
    TEST_ADD(evalution_bishop_x_ray),
    TEST_SUITE_CLOSURE
};


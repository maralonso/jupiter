#include "board.h"
#include "generation.h"
#include "cu/cu.h"
#include "stdio.h"
#include "node.h"
#include "string.h"
#include "pieces/include/pieces.h"

TEST(test_bishop_no_moves)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    square bishop = {FILE_1, COL_C};
    rv = get_bishop_moves(node, bishop); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 1);
}

TEST(test_bishop_moves_right_up)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {BISHOP_W, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square bishop = {FILE_1, COL_A};
    rv = get_bishop_moves(node, bishop); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(8, count);
}

TEST(test_bishop_moves_right_down)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {BISHOP_W, 0, 0, 0, 0, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square bishop = {FILE_8, COL_A};
    rv = get_bishop_moves(node, bishop); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(8, count);
}

TEST(test_bishop_moves_left_up)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {0, 0, 0, 0, 0, 0, 0, BISHOP_W},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square bishop = {FILE_1, COL_H};
    rv = get_bishop_moves(node, bishop); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(8, count);
}

TEST(test_bishop_moves_left_down)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, BISHOP_W}
    };

    memcpy(node->board, board, sizeof(Board));
    square bishop = {FILE_8, COL_H};
    rv = get_bishop_moves(node, bishop); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(8, count);
}

TEST(test_bishop_takes)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, PAWN_B, 0, PAWN_B, 0, 0, 0},
        {0, 0, 0, BISHOP_W, 0, 0, 0, 0},
        {0, 0, PAWN_B, 0, PAWN_B, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square bishop = {FILE_2, COL_B};
    rv = get_bishop_moves(node, bishop); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(5, count);
}

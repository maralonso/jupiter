#include "board.h"
#include "generation.h"
#include "cu/cu.h"
#include "stdio.h"
#include "node.h"
#include "string.h"
#include "pieces/include/pieces.h"

TEST(test_knight_no_moves)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);
    node->board[FILE_3][COL_A] = PAWN_W;
    node->board[FILE_3][COL_C] = PAWN_W;

    square knight = {FILE_1, COL_B};
    rv = get_knight_moves(node, knight); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 1);
}

TEST(test_knight_moves_right_up)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {KNIGHT_W, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square knight = {FILE_1, COL_A};
    rv = get_knight_moves(node, knight); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(3, count);
}

TEST(test_knight_moves_right_down)
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
        {KNIGHT_W, 0, 0, 0, 0, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square knight = {FILE_8, COL_A};
    rv = get_knight_moves(node, knight); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(3, count);
}

TEST(test_knight_moves_left_up)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {0, 0, 0, 0, 0, 0, 0, KNIGHT_W},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square knight = {FILE_1, COL_H};
    rv = get_knight_moves(node, knight); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(3, count);
}

TEST(test_knight_moves_left_down)
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
        {0, 0, 0, 0, 0, 0, 0, KNIGHT_W}
    };

    memcpy(node->board, board, sizeof(Board));
    square knight = {FILE_8, COL_H};
    rv = get_knight_moves(node, knight); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(3, count);
}

TEST(test_knight_takes)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, PAWN_B, 0, PAWN_B, 0, 0, 0},
        {0, PAWN_B, 0, 0, 0, PAWN_B, 0, 0},
        {0, 0, 0, KNIGHT_W, 0, 0, 0, 0},
        {0, PAWN_B, 0, 0, 0, PAWN_B, 0, 0},
        {0, 0, PAWN_B, 0, PAWN_B, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square knight = {FILE_4, COL_D};
    rv = get_knight_moves(node, knight); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(9, count);
}


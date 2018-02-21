#include "board.h"
#include "generation.h"
#include "cu/cu.h"
#include "stdio.h"
#include "node.h"
#include "string.h"
#include "pieces/include/pieces.h"

TEST(test_king_no_moves)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    square king = {FILE_1, COL_E};
    rv = get_king_moves(node, king); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 1);
    
    node->turn = BLACK;
    square king_b = {FILE_8, COL_E};
    rv = get_king_moves(node, king_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 1);
}

TEST(test_king_moves_right_up)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {KING_W, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {KING_B, 0, 0, 0, 0, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square king = {FILE_1, COL_A};
    rv = get_king_moves(node, king); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(4, count);
    
    node->turn = BLACK;
    square king_b = {FILE_8, COL_A};
    rv = get_king_moves(node, king_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 7);
}

TEST(test_king_moves_right_down)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {KING_B, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {KING_W, 0, 0, 0, 0, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square king = {FILE_8, COL_A};
    rv = get_king_moves(node, king); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(4, count);
    
    node->turn = BLACK;
    square king_b = {FILE_1, COL_A};
    rv = get_king_moves(node, king_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 7);
}

TEST(test_king_moves_left_up)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {0, 0, 0, 0, 0, 0, 0, KING_W},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, KING_B}
    };

    memcpy(node->board, board, sizeof(Board));
    square king = {FILE_1, COL_H};
    rv = get_king_moves(node, king); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(4, count);
    
    node->turn = BLACK;
    square king_b = {FILE_8, COL_H};
    rv = get_king_moves(node, king_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 7);
}

TEST(test_king_moves_left_down)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {0, 0, 0, 0, 0, 0, 0, KING_B},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, KING_W}
    };

    memcpy(node->board, board, sizeof(Board));
    square king = {FILE_8, COL_H};
    rv = get_king_moves(node, king); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(4, count);
    
    node->turn = BLACK;
    square king_b = {FILE_1, COL_H};
    rv = get_king_moves(node, king_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 7);
}

TEST(test_king_takes)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, PAWN_B, PAWN_B, PAWN_B, 0, 0, 0},
        {0, 0, PAWN_B, KING_W, PAWN_B, 0, 0, 0},
        {0, 0, PAWN_B, PAWN_B, PAWN_B, 0, 0, 0},
        {0, 0, PAWN_W, PAWN_W, PAWN_W, 0, 0, 0},
        {0, 0, PAWN_W, KING_B, PAWN_W, 0, 0, 0},
        {0, 0, PAWN_W, PAWN_W, PAWN_W, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square king = {FILE_4, COL_D};
    rv = get_king_moves(node, king); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(9, count);
    
    node->turn = BLACK;
    square king_b = {FILE_7, COL_D};
    rv = get_king_moves(node, king_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 17);
}


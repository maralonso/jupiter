#include "board.h"
#include "generation.h"
#include "cu/cu.h"
#include "stdio.h"
#include "node.h"
#include "string.h"
#include "pieces/include/pieces.h"

TEST(test_rook_no_moves)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    square rook = {FILE_1, COL_A};
    rv = get_rook_moves(node, rook); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 1);
    
    node->turn = BLACK;
    square rook_b = {FILE_8, COL_A};
    rv = get_rook_moves(node, rook_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 1);
}

TEST(test_rook_moves_right)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {ROOK_W, 0, 0, 0, 0, 0, 0, 0},
        {PAWN_W, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {PAWN_B, 0, 0, 0, 0, 0, 0, 0},
        {ROOK_B, 0, 0, 0, 0, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square rook = {FILE_1, COL_A};
    rv = get_rook_moves(node, rook); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(8, count);
    
    node->turn = BLACK;
    square rook_b = {FILE_8, COL_A};
    rv = get_rook_moves(node, rook_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 15);
}

TEST(test_rook_moves_left)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {0, 0, 0, 0, 0, 0, 0, ROOK_W},
        {0, 0, 0, 0, 0, 0, 0, PAWN_W},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, PAWN_B},
        {0, 0, 0, 0, 0, 0, 0, ROOK_B}
    };

    memcpy(node->board, board, sizeof(Board));
    square rook = {FILE_1, COL_H};
    rv = get_rook_moves(node, rook); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(8, count);
    
    node->turn = BLACK;
    square rook_b = {FILE_8, COL_H};
    rv = get_rook_moves(node, rook_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 15);
}

TEST(test_rook_moves_up)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {0, 0, 0, 0, 0, 0, PAWN_W, ROOK_W},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, PAWN_B, ROOK_B}
    };

    memcpy(node->board, board, sizeof(Board));
    square rook = {FILE_1, COL_H};
    rv = get_rook_moves(node, rook); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(8, count);
    
    node->turn = BLACK;
    square rook_b = {FILE_8, COL_H};
    rv = get_rook_moves(node, rook_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 15);
}

TEST(test_rook_moves_down)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {ROOK_B, PAWN_B, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {ROOK_W, PAWN_W, 0, 0, 0, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square rook = {FILE_8, COL_A};
    rv = get_rook_moves(node, rook); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(8, count);
    
    node->turn = BLACK;
    square rook_b = {FILE_1, COL_A};
    rv = get_rook_moves(node, rook_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 15);
}

TEST(test_rook_takes)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {0, PAWN_B, 0, 0, 0, 0, 0, 0},
        {PAWN_B, ROOK_W, PAWN_B, 0, 0, 0, 0, 0},
        {0, PAWN_B, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, PAWN_W, 0},
        {0, 0, 0, 0, 0, PAWN_W, ROOK_B, PAWN_W},
        {0, 0, 0, 0, 0, 0, PAWN_W, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square rook = {FILE_2, COL_B};
    rv = get_rook_moves(node, rook); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(5, count);
    
    node->turn = BLACK;
    square rook_b = {FILE_7, COL_G};
    rv = get_rook_moves(node, rook_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 9);
}

TEST(test_rook_attak_square)
{
    Board board = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, ROOK_W, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, ROOK_B, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0,0}
    };

    square rook = {FILE_2, COL_B};
    square sq1 = {FILE_1, COL_B};
    square sq2 = {FILE_7, COL_B};
    square sq3 = {FILE_8, COL_B};
    square sq4 = {FILE_3, COL_D};
    square sq5 = {FILE_4, COL_A};
    assertTrue(rook_attak_square(board, rook,sq1)); 
    assertTrue(rook_attak_square(board, rook,sq2)); 
    assertFalse(rook_attak_square(board, rook, sq3));
    assertFalse(rook_attak_square(board, rook, sq4));
    assertFalse(rook_attak_square(board, rook, sq5));

    square rook_b = {FILE_7, COL_B};
    square sq6 = {FILE_2, COL_B};
    square sq7 = {FILE_8, COL_B};
    square sq8 = {FILE_1, COL_H};
    square sq9 = {FILE_6, COL_D};
    square sq10 = {FILE_5, COL_A};
    assertTrue(rook_attak_square(board, rook_b,sq6)); 
    assertTrue(rook_attak_square(board, rook_b,sq7)); 
    assertFalse(rook_attak_square(board, rook_b, sq8));
    assertFalse(rook_attak_square(board, rook_b, sq9));
    assertFalse(rook_attak_square(board, rook_b, sq10));
}



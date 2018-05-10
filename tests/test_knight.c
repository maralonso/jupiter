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
    node->board[FILE_6][COL_A] = PAWN_B;
    node->board[FILE_6][COL_C] = PAWN_B;

    square knight = {FILE_1, COL_B};
    rv = get_knight_moves(node, knight); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 1);
    
    node->turn = BLACK;
    square knight_b = {FILE_8, COL_B};
    rv = get_knight_moves(node, knight_b); 
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
        {KNIGHT_B, 0, 0, 0, 0, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square knight = {FILE_1, COL_A};
    rv = get_knight_moves(node, knight); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(3, count);
    
    node->turn = BLACK;
    square knight_b = {FILE_8, COL_A};
    rv = get_knight_moves(node, knight_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 5);
}

TEST(test_knight_moves_right_down)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {KNIGHT_B, 0, 0, 0, 0, 0, 0, 0},
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
    
    node->turn = BLACK;
    square knight_b = {FILE_1, COL_A};
    rv = get_knight_moves(node, knight_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 5);
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
        {0, 0, 0, 0, 0, 0, 0, KNIGHT_B}
    };

    memcpy(node->board, board, sizeof(Board));
    square knight = {FILE_1, COL_H};
    rv = get_knight_moves(node, knight); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(3, count);
    
    node->turn = BLACK;
    square knight_b = {FILE_8, COL_H};
    rv = get_knight_moves(node, knight_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 5);
}

TEST(test_knight_moves_left_down)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {0, 0, 0, 0, 0, 0, 0, KNIGHT_B},
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
    
    node->turn = BLACK;
    square knight_b = {FILE_1, COL_H};
    rv = get_knight_moves(node, knight_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 5);
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
        {0, PAWN_B, PAWN_W, 0, PAWN_W, PAWN_B, 0, 0},
        {0, PAWN_W, 0, KNIGHT_W, 0, PAWN_W, 0, 0},
        {0, PAWN_B, 0, KNIGHT_B, 0, PAWN_B, 0, 0},
        {0, PAWN_W, PAWN_B, 0, PAWN_B, PAWN_W, 0, 0},
        {0, 0, PAWN_W, 0, PAWN_W, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square knight = {FILE_4, COL_D};
    rv = get_knight_moves(node, knight); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(9, count);
    
    node->turn = BLACK;
    square knight_b = {FILE_5, COL_D};
    rv = get_knight_moves(node, knight_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 17);
}

TEST(test_knight_attak_square)
{
    Board board = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, KNIGHT_W, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, KNIGHT_B, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0,0, 0},
        {0, 0, 0, 0, 0, 0, 0,0}
    };

    square knight = {FILE_3, COL_C};
    square sq1 = {FILE_4, COL_E};
    square sq2 = {FILE_5, COL_D};
    square sq3 = {FILE_7, COL_G};
    square sq4 = {FILE_3, COL_D};
    square sq5 = {FILE_4, COL_B};
    assertTrue(knight_attak_square(board, knight,sq1)); 
    assertTrue(knight_attak_square(board, knight,sq2)); 
    assertFalse(knight_attak_square(board, knight, sq3));
    assertFalse(knight_attak_square(board, knight, sq4));
    assertFalse(knight_attak_square(board, knight, sq5));
 
    square knight_b = {FILE_6, COL_C};
    square sq6 = {FILE_5, COL_E};
    square sq7 = {FILE_4, COL_D};
    square sq8 = {FILE_6, COL_C};
    square sq9 = {FILE_6, COL_D};
    square sq10 = {FILE_5, COL_B};
    assertTrue(knight_attak_square(board, knight_b,sq6)); 
    assertTrue(knight_attak_square(board, knight_b,sq7)); 
    assertFalse(knight_attak_square(board, knight_b, sq8));
    assertFalse(knight_attak_square(board, knight_b, sq9));
    assertFalse(knight_attak_square(board, knight_b, sq10));
}

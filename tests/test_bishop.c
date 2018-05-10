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
    
    node->turn = BLACK;
    square bishop_b = {FILE_8, COL_C};
    rv = get_bishop_moves(node, bishop_b); 
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
        {BISHOP_B, 0, 0, 0, 0, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square bishop = {FILE_1, COL_A};
    rv = get_bishop_moves(node, bishop); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(8, count);
    
    node->turn = BLACK;
    square bishop_b = {FILE_8, COL_A};
    rv = get_bishop_moves(node, bishop_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(15, count);
}

TEST(test_bishop_moves_right_down)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {BISHOP_B, 0, 0, 0, 0, 0, 0, 0},
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
    
    node->turn = BLACK;
    square bishop_b = {FILE_1, COL_A};
    rv = get_bishop_moves(node, bishop_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(15, count);
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
        {0, 0, 0, 0, 0, 0, 0, BISHOP_B}
    };

    memcpy(node->board, board, sizeof(Board));
    square bishop = {FILE_1, COL_H};
    rv = get_bishop_moves(node, bishop); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(8, count);
    
    node->turn = BLACK;
    square bishop_b = {FILE_8, COL_H};
    rv = get_bishop_moves(node, bishop_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(15, count);
}

TEST(test_bishop_moves_left_down)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {0, 0, 0, 0, 0, 0, 0, BISHOP_B},
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
    
    node->turn = BLACK;
    square bishop_b = {FILE_1, COL_H};
    rv = get_bishop_moves(node, bishop_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(15, count);
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
        {0, 0, PAWN_W, 0, PAWN_W, 0, 0, 0},
        {0, 0, 0, BISHOP_B, 0, 0, 0, 0},
        {0, 0, PAWN_W, 0, PAWN_W, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square bishop = {FILE_4, COL_D};
    rv = get_bishop_moves(node, bishop); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(5, count);
    
    node->turn = BLACK;
    square bishop_b = {FILE_7, COL_D};
    rv = get_bishop_moves(node, bishop_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(9, count);
}

TEST(test_bishop_attak_square)
{
    Board board = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, BISHOP_W, 0, 0, 0, 0, PAWN_W, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, BISHOP_B, 0, 0, 0, 0, PAWN_B, 0},
        {0, 0, 0, 0, 0, 0, 0,0}
    };

    square bishop = {FILE_2, COL_B};
    square sq1 = {FILE_7, COL_G};
    square sq2 = {FILE_6, COL_F};
    square sq3 = {FILE_8, COL_H};
    square sq4 = {FILE_3, COL_D};
    square sq5 = {FILE_4, COL_B};
    assertTrue(bishop_attak_square(board, bishop,sq1)); 
    assertTrue(bishop_attak_square(board, bishop,sq2)); 
    assertFalse(bishop_attak_square(board, bishop, sq3));
    assertFalse(bishop_attak_square(board, bishop, sq4));
    assertFalse(bishop_attak_square(board, bishop, sq5));

    square bishop_b = {FILE_7, COL_B};
    square sq6 = {FILE_2, COL_G};
    square sq7 = {FILE_3, COL_F};
    square sq8 = {FILE_1, COL_H};
    square sq9 = {FILE_6, COL_D};
    square sq10 = {FILE_5, COL_B};
    assertTrue(bishop_attak_square(board, bishop_b,sq6)); 
    assertTrue(bishop_attak_square(board, bishop_b,sq7)); 
    assertFalse(bishop_attak_square(board, bishop_b, sq8));
    assertFalse(bishop_attak_square(board, bishop_b, sq9));
    assertFalse(bishop_attak_square(board, bishop_b, sq10));
}



#include "board.h"
#include "generation.h"
#include "cu/cu.h"
#include "stdio.h"
#include "node.h"
#include "string.h"
#include "pieces/include/pieces.h"

TEST(test_pawn_no_moves)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);
    node->board[FILE_3][COL_A] = PAWN_B;
    node->board[FILE_6][COL_A] = PAWN_W;

    square pawn = {FILE_2, COL_A};
    rv = get_pawn_moves(node, pawn); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 1);

    node->turn = BLACK;
    square pawn_b = {FILE_7, COL_A};
    rv = get_pawn_moves(node, pawn_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 1);
}

TEST(test_pawn_moves_fordward)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {PAWN_W, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {PAWN_B, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square pawn = {FILE_2, COL_A};
    rv = get_pawn_moves(node, pawn); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(3, count);
    
    node->turn = BLACK;
    square pawn_b = {FILE_7, COL_A};
    rv = get_pawn_moves(node, pawn_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(5, count);
}

TEST(test_pawn_takes)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, PAWN_W, 0, 0, 0, 0, 0, 0},
        {PAWN_B, KNIGHT_W, PAWN_B, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {PAWN_W, KNIGHT_B, PAWN_W, 0, 0, 0, 0, 0},
        {0, PAWN_B, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    square pawn = {FILE_2, COL_B};
    rv = get_pawn_moves(node, pawn); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(3, count);
    
    node->turn = BLACK;
    square pawn_b = {FILE_7, COL_B};
    rv = get_pawn_moves(node, pawn_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(5, count);
}

TEST(test_pawn_passant)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, KNIGHT_B, 0},
        {0, 0, 0, 0, 0, PAWN_W, PAWN_B, 0},
        {0, PAWN_W, PAWN_B, 0, 0, 0, 0, 0},
        {0, KNIGHT_W, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };

    memcpy(node->board, board, sizeof(Board));
    node->passant = COL_C;
    square pawn = {FILE_5, COL_B};
    rv = get_pawn_moves(node, pawn); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(2, count);
    
    node->turn = BLACK;
    node->passant = COL_F;
    square pawn_b = {FILE_4, COL_G};
    rv = get_pawn_moves(node, pawn_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(3, count);
}

TEST(test_pawn_promote)
{
    Node_t *node;
    retval_t rv;
    uint32_t count;
    rv = move_init(&node);

    Board board = {
        {0, 0, 0, 0, 0, ROOK_W, 0, ROOK_W},
        {0, 0, 0, 0, 0, 0, PAWN_B, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, PAWN_W, 0, 0, 0, 0, 0, 0},
        {ROOK_B, 0, ROOK_B, 0, 0, 0, 0,0}
    };

    memcpy(node->board, board, sizeof(Board));
    square pawn = {FILE_7, COL_B};
    rv = get_pawn_moves(node, pawn); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(10, count);
    
    node->turn = BLACK;
    square pawn_b = {FILE_2, COL_G};
    rv = get_pawn_moves(node, pawn_b); 
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(19, count);
}

TEST(test_pawn_attak_square)
{
    Board board = {
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, PAWN_W, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, PAWN_B, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0,0}
    };

    square pawn = {FILE_2, COL_B};
    square sq1 = {FILE_3, COL_A};
    square sq2 = {FILE_3, COL_C};
    square sq3 = {FILE_3, COL_B};
    square sq4 = {FILE_3, COL_D};
    square sq5 = {FILE_4, COL_B};
    assertTrue(pawn_attak_square(board, pawn,sq1)); 
    assertTrue(pawn_attak_square(board, pawn,sq2)); 
    assertFalse(pawn_attak_square(board, pawn, sq3));
    assertFalse(pawn_attak_square(board, pawn, sq4));
    assertFalse(pawn_attak_square(board, pawn, sq5));

    square pawn_b = {FILE_7, COL_B};
    square sq6 = {FILE_6, COL_A};
    square sq7 = {FILE_6, COL_C};
    square sq8 = {FILE_6, COL_B};
    square sq9 = {FILE_6, COL_D};
    square sq10 = {FILE_5, COL_B};
    assertTrue(pawn_attak_square(board, pawn_b,sq6)); 
    assertTrue(pawn_attak_square(board, pawn_b,sq7)); 
    assertFalse(pawn_attak_square(board, pawn_b, sq8));
    assertFalse(pawn_attak_square(board, pawn_b, sq9));
    assertFalse(pawn_attak_square(board, pawn_b, sq10));
}

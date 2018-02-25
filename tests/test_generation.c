#include "board.h"
#include "generation.h"
#include "cu/cu.h"
#include "stdio.h"
#include "node.h"
#include <string.h>


TEST(test_move_init)
{
    Node_t *node;
    retval_t rv;
    rv = move_init(&node);
    
    assertEquals(rv, RV_SUCCESS);
    assertEquals(node->value, 0);
    assertEquals(node->turn, WHITE);
    assertEquals(node->check_status, NOT_CHECK);
    assertEquals(node->castles, ALL_CASTLES);
    assertEquals(node->passant, 0);
    assertEquals(node->child, NULL);
    assertEquals(node->next, NULL);
    assertEquals(node->parent, NULL);
    
    int i,j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            assertEquals(node->board[i][j], initial_board[i][j]);
        }
    }
}

TEST(test_node_init_fail)
{
    retval_t rv;

    rv = move_init(NULL);
    assertEquals(rv, RV_ERROR);
}

TEST(test_insert_move)
{
    uint32_t count;
    Node_t *node;
    retval_t rv;
    rv = move_init(&node);
    assertEquals(rv, RV_SUCCESS);

    Move_t mov = {{0, 0}, {0,0}};
    rv = insert_move(node, mov);
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 2);

    rv = insert_move(node, mov);
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 3);

    rv = insert_move(node, mov);
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 4);

    //TODO Check Node fields
}

TEST(test_insert_move_fail)
{
    Move_t mov = {{0, 0}, {0,0}};
    retval_t rv = insert_move(NULL, mov);
    assertEquals(rv, RV_ERROR);
} 

TEST(test_square_attaked)
{
    Node_t *node;
    move_init(&node);

    Board board = {
        {QUEEN_W, ROOK_W, 0, 0, 0, 0, 0, 0},
        {0, BISHOP_W, KNIGHT_W, 0, 0, 0, PAWN_W, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, BISHOP_B, KNIGHT_B, 0, 0, 0, PAWN_B, 0},
        {QUEEN_B, ROOK_B, 0, 0, 0, 0, 0,0}
    };

    node->turn = BLACK;
    memcpy(node->board, board, sizeof(Board));
    square sq1 = {FILE_7, COL_A};
    square sq2 = {FILE_1, COL_H};
    square sq3 = {FILE_7, COL_G};
    square sq4 = {FILE_3, COL_H};
    square sq5 = {FILE_4, COL_D};
    square sq11 = {FILE_5, COL_B};
    square sq21 = {FILE_8, COL_C};
    square sq31 = {FILE_3, COL_B};
    square sq41 = {FILE_2, COL_D};
    square sq51 = {FILE_8, COL_G};
    assertTrue(square_attaked(node, sq1)); 
    assertTrue(square_attaked(node, sq2)); 
    assertTrue(square_attaked(node, sq3)); 
    assertTrue(square_attaked(node, sq4)); 
    assertTrue(square_attaked(node, sq5)); 
    assertFalse(square_attaked(node, sq11)); 
    assertFalse(square_attaked(node, sq11)); 
    assertFalse(square_attaked(node, sq21)); 
    assertFalse(square_attaked(node, sq31)); 
    assertFalse(square_attaked(node, sq41)); 
    assertFalse(square_attaked(node, sq51)); 

    node->turn = WHITE;
    square sq6 = {FILE_1, COL_A};
    square sq7 = {FILE_8, COL_H};
    square sq8 = {FILE_2, COL_G};
    square sq9 = {FILE_6, COL_H};
    square sq10 = {FILE_5, COL_D};
    assertTrue(square_attaked(node, sq6)); 
    assertTrue(square_attaked(node, sq7)); 
    assertTrue(square_attaked(node, sq8)); 
    assertTrue(square_attaked(node, sq9)); 
    assertTrue(square_attaked(node, sq10)); 

}

TEST(test_clear_castles)
{
    Node_t *node;
    retval_t rv;
    move_init(&node);

    Board board = {
        {ROOK_W, 0, 0, 0, KING_W, 0, 0, ROOK_W},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {ROOK_B, 0, 0, 0, KING_B, 0, 0,ROOK_B}
    };

    memcpy(node->board, board, sizeof(Board));
    Move_t m1 = {{FILE_1, COL_H}, {FILE_2, COL_H}};
    Move_t m2 = {{FILE_1, COL_A}, {FILE_2, COL_A}};
    Move_t m3 = {{FILE_1, COL_E}, {FILE_2, COL_E}};

    rv = insert_move(node, m1);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(node->child->castles, (ALL_CASTLES & (~W_SHORT_CASTLE)));
    delete_node(node->child);

    node->castles = ALL_CASTLES;
    rv = insert_move(node, m2);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(node->child->castles, (ALL_CASTLES & (~W_LONG_CASTLE)));
    delete_node(node->child);
    
    node->castles = ALL_CASTLES;
    rv = insert_move(node, m3);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(node->child->castles, (ALL_CASTLES & (~W_CASTLES)));
    delete_node(node->child);
    
    node->turn = BLACK;
    node->castles = ALL_CASTLES;
    Move_t m4 = {{FILE_8, COL_H}, {FILE_7, COL_H}};
    Move_t m5 = {{FILE_8, COL_A}, {FILE_7, COL_A}};
    Move_t m6 = {{FILE_8, COL_E}, {FILE_7, COL_E}};

    rv = insert_move(node, m4);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(node->child->castles, (ALL_CASTLES & (~B_SHORT_CASTLE)));
    delete_node(node->child);
    
    node->castles = ALL_CASTLES;
    rv = insert_move(node, m5);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(node->child->castles, (ALL_CASTLES & (~B_LONG_CASTLE)));
    delete_node(node->child);
    
    node->castles = ALL_CASTLES;
    rv = insert_move(node, m6);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(node->child->castles, (ALL_CASTLES & (~B_CASTLES)));
    delete_node(node->child);
}

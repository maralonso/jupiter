#include "board.h"
#include "generation.h"
#include "cu/cu.h"
#include "stdio.h"
#include "node.h"


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

#include "board.h"
#include "generation.h"
#include "cu/cu.h"
#include "stdio.h"


TEST(test_node_init)
{
    Node_t node;
    retval_t rv;

    rv = node_init(&node);

    assertEquals(rv, RV_SUCCESS);
    assertEquals(node.value, 0);
    assertEquals(node.turn, WHITE);
    assertEquals(node.check_status, NOT_CHECK);
    assertEquals(node.castles, ALL_CASTLES);
    assertEquals(node.child, NULL);
    assertEquals(node.next, NULL);
    assertEquals(node.parent, NULL);
    
    int i,j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            assertEquals(node.board[i][j], initial_board[i][j]);
        }
    }
}

TEST(test_node_initi_fail)
{
    retval_t rv;

    rv = node_init(NULL);
    assertEquals(rv, RV_ERROR);
}

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
}

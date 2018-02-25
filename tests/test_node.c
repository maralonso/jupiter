#include "board.h"
#include "generation.h"
#include "cu/cu.h"
#include "stdio.h"
#include "node.h"
#include "string.h"
#include "pieces/include/pieces.h"

TEST(test_insert_node)
{
    Node_t *node, *new, *new1, *new2;
    retval_t rv;
    uint32_t count;
   
    rv = move_init(&node);
    assertEquals(rv, RV_SUCCESS);
    rv = move_init(&new);
    assertEquals(rv, RV_SUCCESS);
    rv = move_init(&new1);
    assertEquals(rv, RV_SUCCESS);
    rv = move_init(&new2);
    assertEquals(rv, RV_SUCCESS);

    insert_node(node, new);
    count = get_tree_count(node);
    assertEquals(count, 2);
    
    insert_node(node, new1);
    count = get_tree_count(node);
    assertEquals(count, 3);
    
    insert_node(new, new2);
    count = get_tree_count(node);
    assertEquals(count, 4);

    delete_node(node);
}


TEST(test_delete_node)
{
    Node_t *node, *new, *new1, *new2;
    uint32_t count;
   
    move_init(&node);
    move_init(&new);
    move_init(&new1);
    move_init(&new2);

    insert_node(node, new);
    insert_node(node, new1);
    insert_node(new, new2);
    count = get_tree_count(node);
    assertEquals(count, 4);

    delete_node(new);
    count = get_tree_count(node);
    assertEquals(count, 2);

    delete_node(new1);
    count = get_tree_count(node);
    assertEquals(count, 1);
}

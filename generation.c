#include "board.h"
#include <string.h>

static void copy_initial_board(Board *board)
{
    memcpy(board, initial_board, sizeof(initial_board));
}

retval_t node_init(Node_t *node)
{
    if (node == NULL) {
        return RV_ERROR;
    }
    
    copy_initial_board(node->board);

    node->notation      = "";
    node->value         = 0;
    node->turn          = WHITE;
    node->chech_status  = NOT_CHECK;
    node-castles        = ALL_CASTLES;

    node->child         = NULL; 
    node->next          = NULL; 
    node->parent        = NULL; 
}

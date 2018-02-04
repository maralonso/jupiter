#include "board.h"
#include <string.h>

extern  retval_t EVALUATE_BOARD(Node_t *node, Evaluation_Function func);

static void copy_initial_board(Board *board)
{
    memcpy(board, initial_board, sizeof(initial_board));
}

static retval_t get_piece_moves(Node_t *node, uint8_t rank, uint8_t file)
{
    switch(node->board[rank][file] * node->turn) {
        case PAWN:
            break;
        case ROOK:
            break;
        case KNIGHT:
            break;
        case BISHOP:
            break;
        case QUEEN:
            break;
        case KING:
            break;
        default:
            break;
    }

    return RV_SUCCESS;
}

retval_t node_init(Node_t *node)
{
    if (node == NULL) {
        return RV_ERROR;
    }
    
    copy_initial_board(&node->board);
    strcpy(node->notation, "");

    node->value         = 0;
    node->turn          = WHITE;
    node->check_status  = NOT_CHECK;
    node->castles        = ALL_CASTLES;

    node->child         = NULL; 
    node->next          = NULL; 
    node->parent        = NULL; 

    return RV_SUCCESS;
}

retval_t get_moves(Node_t *node)
{
    return EVALUATE_BOARD(node, get_piece_moves);
}

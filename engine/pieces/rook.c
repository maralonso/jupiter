#include "board.h"
#include "pieces.h"

static retval_t rook_eval(Node_t *node, square sq, uint8_t file, uint8_t col)
{
    if ((col == sq[0] && file != sq[1]) ||
        (col != sq[0] && file == sq[1])) {

        if ((node->board[file][col] * node->turn) <= 0) {
             //insert node          
        }

        if (node->board[file][col] != 0) {
            //return
        }
    }

    return RV_SUCCESS;
}

retval_t get_rook_moves(Node_t *node, square sq)
{
    uint8_t rotation = ROTATION_0 | ROTATION_90 | ROTATION_180 | ROTATION_270;
    return eval_with_rotation(node, sq, rotation, rook_eval); 
}


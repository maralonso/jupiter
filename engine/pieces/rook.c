#include "board.h"
#include "pieces.h"
#include "generation.h"

#include <stdio.h>

static retval_t rook_eval(Node_t *node, square sq, uint8_t file, uint8_t col)
{
    if ((file == sq[0] && col != sq[1]) ||
        (file != sq[0] && col == sq[1])) {

        if ((node->board[file][col] * node->turn) <= 0) {
            Move_t mov = {{sq[0], sq[1]}, {file, col}};
            SUCCES_OR_RETURN(insert_move(node, mov));
        }

        if (node->board[file][col] != 0) {
            return RV_NO_MOVE_LEFT;
        }
    }

    return RV_SUCCESS;
}

retval_t get_rook_moves(Node_t *node, square sq)
{
    uint8_t rotation = ROTATION_0 | ROTATION_90 | ROTATION_180 | ROTATION_270;
    return eval_with_rotation(node, sq, rotation, rook_eval); 
}


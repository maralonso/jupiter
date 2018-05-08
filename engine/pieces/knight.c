#include <stdlib.h>
#include "board.h"
#include "pieces.h"
#include "generation.h"

static retval_t knight_moves(Node_t *node, square sq, uint8_t file, uint8_t col)
{
    if ((abs(file - sq[0]) == 1 && abs(col - sq[1]) == 2) ||
        (abs(file - sq[0]) == 2 && abs(col - sq[1]) == 1)) {

        if ((node->board[file][col] * node->turn) <= 0) {
            Move_t mov = {{sq[0], sq[1]}, {file, col}};
            SUCCES_OR_RETURN(insert_move(node, mov));
        }
    }

    return RV_SUCCESS;
}

retval_t get_knight_moves(Node_t *node, square sq)
{
    uint8_t rotation = ROTATION_0 | ROTATION_90 | ROTATION_180 | ROTATION_270;
    return exec_with_rotation(node, sq, rotation, knight_moves); 
}

bool knight_attak_square(Board board,  square from, square to)
{
    if ((abs(from[0] - to[0]) == 1 && abs(from[1] - to[1]) == 2) ||
        (abs(from[0] - to[0]) == 2 && abs(from[1] - to[1]) == 1)) {
            return true;
    }

    return false;
}

int32_t knight_evaluation(Board board, uint8_t file, uint8_t rank)
{
    //TODO
    return 0;
}

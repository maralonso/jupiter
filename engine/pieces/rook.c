#include "board.h"
#include "pieces.h"
#include "generation.h"

static retval_t rook_moves(Node_t *node, square sq, uint8_t file, uint8_t col)
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
    return exec_with_rotation(node, sq, rotation, rook_moves); 
}

bool rook_attak_square(Node_t *node, square from, square to)
{
    int8_t rank_step =0;
    int8_t file_step =0;
    
    if ((from[0] == to[0] && from[1] != to[1]) ||
        (from[0] != to[0] && from[1] == to[1])) {
        
        if (from[0] != to[0]) {
            file_step = from[0] < to[0] ? 1: -1;
        }
        if (from[1] != to[1]) {
            rank_step = from[1] < to[1] ? 1: -1;
        }
        for (int8_t i = from[0] + file_step, j = from[1] + rank_step;
             i != to[0] || j != to[1]; i += file_step, j += rank_step) {
            if (node->board[i][j] != 0) {
                return false;
            }
        }   
        return true;
    }
    return false;
}

int32_t rook_evaluation(Board board, uint8_t file, uint8_t rank)
{
    //TODO
    return 0;
}

#include <stdlib.h>
#include "board.h"
#include "pieces.h"
#include "generation.h"
#include "evaluation.h"

static int8_t square_table[8][8] = {
    {-5,-4,-3,-3,-3,-3,-4,-5},
    {-4,-2,  0,  5,  5,  0,-2,-4},
    {-3,  5, 10, 15, 15, 10, 5,-3},
    {-3,  5, 15, 20, 20, 15, 5,-3},
    {-3,  5, 15, 20, 20, 15, 5,-3},
    {-3,  5, 10, 15, 15, 10, 5,-3},
    {-4,-2, 0, 5, 5, 0,-2,-4},
    {-5,-4,-3,-3,-3,-3,-4,-5}
};

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

static bool supported_knight(Board board, uint8_t file, uint8_t rank)
{
    int8_t turn = TURN(board, file, rank);

    if ((file - turn) <= FILE_1 || (file - turn) >= FILE_8) {
        return false;
    }

    if ((((rank - 1) > COL_A) && board[file - turn][rank - 1] == (PAWN * turn)) || 
        (((rank + 1) < COL_H) && board[file - turn][rank + 1] == (PAWN * turn))) {
        return true;
    }

    return false;
}

int32_t knight_evaluation(Board board, uint8_t file, uint8_t rank)
{
    int32_t eval = 0;
    int8_t turn = TURN(board, file, rank);

    eval += square_table[file][rank];

    if (supported_knight(board, file, rank)) {
        eval += KNIGHT_SUPOORTED_POND;
    }
    
    return eval * turn;
}

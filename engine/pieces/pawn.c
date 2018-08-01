#include <stdlib.h>
#include "board.h"
#include "pieces.h"
#include "generation.h"
#include "evaluation.h"

static retval_t pawn_takes(Node_t *node, square sq, uint8_t file, uint8_t col)
{
    if (file == (sq[0] + node->turn) && (abs(col - sq[1]) == 1)) {

        if ((node->board[file][col] * node->turn) < 0) {
            Move_t mov = {{sq[0], sq[1]}, {file, col}};
            SUCCES_OR_RETURN(insert_move(node, mov));
        }
    }
    return RV_SUCCESS;
}

static retval_t pawn_moves(Node_t *node, square sq, uint8_t file, uint8_t col)
{
    if ((col == sq[1])  && (file == (sq[0] + node->turn))) {
        if ((node->board[file][col] == 0)) {
            Move_t mov = {{sq[0], sq[1]}, {file, col}};
            SUCCES_OR_RETURN(insert_move(node, mov));
        }
    }
    if (sq[0] == ((node->turn + 7) % 7) &&
       col == sq[1]  &&  file == (sq[0] + (2 * node->turn)) &&
       node->board[file - node->turn][col] == 0) {
        if ((node->board[file][col] == 0)) {
            Move_t mov = {{sq[0], sq[1]}, {file, col}};
            SUCCES_OR_RETURN(insert_move(node, mov));
        }
    }
    return RV_SUCCESS;
}

static retval_t pawn_promote(Node_t *node, square sq, uint8_t file, uint8_t col)
{

    if (file == (sq[0] + node->turn) && (((abs(col - sq[1]) == 1) &&
       (node->board[file][col] * node->turn) < 0) ||
       (col == sq[1] && ((node->board[file][col] == 0))))) {
            Move_t mov = {{sq[0], sq[1]}, {file, col}};
            SUCCES_OR_RETURN(insert_promotion(node, mov));
    }
    return RV_SUCCESS;
}

static retval_t pawn_passant(Node_t *node, square sq, uint8_t file, uint8_t col)
{
    if (node->passant == col && ((node->board[file][col] * node->turn) < 0) &&
        file == sq[0]  && abs(col -sq[1]) == 1) {
            Move_t mov = {{sq[0], sq[1]}, {file, col}};
            SUCCES_OR_RETURN(insert_passant(node, mov));
    }
    return RV_SUCCESS;
}

retval_t get_pawn_moves(Node_t *node, square sq)
{
    retval_t rv;
    uint8_t rotation = ROTATION_0 | ROTATION_270;

    if (node->turn == BLACK) {
        rotation = ~rotation;
    }

    if ((sq[0] + node->turn) % 7 == 0) {
        return exec_with_rotation(node, sq, rotation, pawn_promote);
    } else {
        rv = exec_with_rotation(node, sq, rotation, pawn_takes);
        SUCCES_OR_RETURN(rv);

        if ((sq[0] + (3 * node->turn)) % 7 == 0) {
            rv = exec_with_rotation(node, sq, rotation, pawn_passant);
            SUCCES_OR_RETURN(rv);
        }

        return exec_with_rotation(node, sq, rotation, pawn_moves);
    }
}

bool pawn_attak_square(Board board, square from, square to)
{
    int8_t turn = TURN(board, from[0], from[1]);

    if (from[0] == (to[0] - turn) &&
        abs(from[1] - to[1]) == 1) {
        return true;
    }

    return false;
}

static bool isolated_pawn(Board board, uint8_t file, uint8_t rank)
{
    int8_t pawn = board[file][rank];

    for (int i = FILE_2; i < FILE_8; i++) {
        if (rank > COL_A) {
            if (board[i][rank - 1] == pawn) {
                return false;
            }
        }
        if (rank < COL_H) {
            if (board[i][rank + 1] == pawn) {
                return false;
            }
        } 
    }

    return true;                 
}

static bool passed_pawn(Board board, uint8_t file, uint8_t rank)
{
    int8_t step = board[file][rank];
    int8_t pawn = board[file][rank] * -1;

    for (int i = file; i < FILE_8 && i > FILE_1; i += step) {
        if (rank > COL_A) {
            if (board[i][rank - 1] == pawn) {
                return false;
            }
        }
        if (rank < COL_H) {
            if (board[i][rank + 1] == pawn) {
                return false;
            }
        } 
    }

    return true;                 
}

static bool doubled_pawn(Board board, uint8_t file, uint8_t rank)
{
    int8_t pawn = board[file][rank];

    for (int i = FILE_2; i < FILE_8; i++) {
        if (board[i][rank] == pawn && i != file) {
            return true;
        }
    }

    return false;
}

int32_t pawn_evaluation(Board board, uint8_t file, uint8_t rank)
{
    int32_t evaluation = 0;
    int8_t turn = TURN(board, file, rank);

    if (isolated_pawn(board, file, rank)) {
        evaluation -= ISOLATED_PAWN_POND;
    }

    if (doubled_pawn(board, file, rank)) {
        evaluation -= DOUBLED_PAWN_POND;
    }

    if (passed_pawn(board, file, rank)) {
        evaluation += PASSED_PAWN_POND;
    }

    return evaluation * turn;
}

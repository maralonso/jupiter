#include "board.h"
#include "pieces.h"
#include "generation.h"
#include "evaluation.h"

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

bool rook_attak_square(Board board, square from, square to)
{
    int8_t rank_step =0;
    int8_t file_step =0;
    
    if (board[from[0]][from[1]] * board[to[0]][to[1]] > 0) {
        return false;
    }

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
            if (board[i][j] != 0) {
                return false;
            }
        }   
        return true;
    }
    return false;
}

static bool connected_rooks(Board board, uint8_t file, uint8_t rank)
{
    int16_t rook = board[file][rank];

    for (int i = FILE_1; i <= FILE_8; i++) {
        if (board[i][rank] == rook && i != file) {
            return true;
        }
    }

    for (int i = COL_A; i <= COL_H; i++) {
        if (board[file][i] == rook && i != rank) {
            return true;
        }
    }

    return false;
}

static uint8_t available_rook_moves(Board board, uint8_t file, uint8_t rank)
{
    uint8_t count = 0;
    square from = {file, rank};

    for (int i = FILE_1; i <= FILE_8; i++) {
        square to = {i, rank};

        if (rook_attak_square(board, from, to)) {
            count++;
        }
    }
   
    for (int i = COL_A; i <= COL_H; i++) {
        square to = {file, i};

        if (rook_attak_square(board, from, to)) {
            count++;
        }
    }

    return count;
}

static bool x_ray(Board board, uint8_t file, uint8_t rank)
{
    int8_t not_turn = NOT_TURN(board, file, rank);
    square from = {file, rank};

    for (int i = FILE_1; i <= FILE_8; i++) {
        square to = {i, rank};
        if ((board[i][rank] == (QUEEN * not_turn) || 
            board[i][rank] == (KING * not_turn)) &&
            (!(rook_attak_square(board, from, to)))) {
            return true;
        }
    }

    for (int i = COL_A; i <= COL_H; i++) {
        square to = {file, i};
        if ((board[file][i] == (QUEEN * not_turn) || 
            board[file][i] == (KING * not_turn)) &&
            !((rook_attak_square(board, from, to)))) {
            return true;
        }
    }
        
    return false;
}

int32_t rook_evaluation(Board board, uint8_t file, uint8_t rank)
{
    int32_t eval = 0;
    int8_t turn = TURN(board, file, rank);

    eval += available_rook_moves(board, file, rank);

    if (connected_rooks(board, file, rank)) {
            eval += CONNECTED_ROOKS_POND;
    }

    if (x_ray(board, file, rank)) {
        eval += ROOK_X_RAY_POND;
    }

    return eval * turn;
}

#include <stdlib.h>
#include "board.h"
#include "pieces.h"
#include "generation.h"
#include "evaluation.h"

static retval_t bishop_moves(Node_t *node, square sq, uint8_t file, uint8_t col)
{
    if (abs(file - sq[0]) == abs(col - sq[1])) {

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

retval_t get_bishop_moves(Node_t *node, square sq)
{
    uint8_t rotation = ROTATION_0 | ROTATION_90 | ROTATION_180 | ROTATION_270;
    return exec_with_rotation(node, sq, rotation, bishop_moves); 
}

bool bishop_attak_square(Board board, square from, square to)
{
    if (board[from[0]][from[1]] * board[to[0]][to[1]] > 0) {
        return false;
    }

    if (abs(from[0] - to[0]) == abs(from[1] - to[1])) {
        int8_t file_step = (to[0] - from[0]) > 0 ? 1: -1;
        int8_t rank_step = (to[1] - from[1]) > 0 ? 1: -1;
        for (int8_t i = from[0] + file_step, j = from[1] + rank_step;
             i != to[0] && j != to[1]; i += file_step, j += rank_step) {
            if (board[i][j] != 0) {
                return false;
            }
        }   
        return true;
    }
  
    return false;
}

static bool unexpulsable_bishop(Board board, uint8_t file, uint8_t rank)
{
    int8_t turn = TURN(board, file, rank);
    int8_t not_turn = NOT_TURN(board, file, rank);

    for (int i = file + turn; i >= FILE_1 && i <= FILE_8; i += turn) {
        if (((rank - 1) >= COL_A && board[i][rank - 1] == (PAWN * not_turn)) ||
            ((rank + 1) <= COL_H && board[i][rank + 1] == (PAWN * not_turn))) {
            return false;
        }
    }

    return true;
}

static bool supported_bishop(Board board, uint8_t file, uint8_t rank)
{
    int8_t turn = TURN(board, file, rank);

    if ((file - turn) <= FILE_1 || (file - turn) >= FILE_8) {
        return false;
    }

    if ((((rank - 1) >= COL_A) && board[file - turn][rank - 1] == (PAWN * turn)) || 
        (((rank + 1) <= COL_H) && board[file - turn][rank + 1] == (PAWN * turn))) {
        return true;
    }  

    return false;
}

static uint8_t available_bishop_moves(Board board, uint8_t file, uint8_t  rank)
{
    uint8_t count = 0;
    square from = {file, rank};
    int8_t start_file, start_rank;

    for (start_file = file, start_rank = rank;
         start_file > FILE_1 && start_rank > COL_A;
         start_file--, start_rank--);

    for (int i = start_file, j = start_rank;
         i <= FILE_8 && j <= COL_H;  i++, j++) {
        square to = {i, j};
        if (bishop_attak_square(board, from, to)) {
            count++;
        }
    }
            
    for (start_file = file, start_rank = rank;
         start_file < FILE_8 && start_rank > COL_A;
         start_file++, start_rank--);

    for (int i = start_file, j = start_rank;
         i >= FILE_1 && j <= COL_H;  i--, j++) {
        square to = {i, j};
        if (bishop_attak_square(board, from, to)) {
            count++;
        }
    }

    return count;
}

static bool x_ray(Board board, uint8_t file, uint8_t rank)
{
    int8_t not_turn = NOT_TURN(board, file,rank);
    square from = {file, rank};
    int8_t start_file, start_rank;

    for (start_file = file, start_rank = rank;
         start_file > FILE_1 && start_rank > COL_A;
         start_file--, start_rank--);

    for (int i = start_file, j = start_rank;
         i <= FILE_8 && j <= COL_H;  i++, j++) {
        square to = {i, j};
        if ((i != file) && (board[i][j] == (QUEEN * not_turn) ||
             board[i][j] == (KING * not_turn)) &&
           (!bishop_attak_square(board, from, to))) {
            return true;
        }
    }
            
    for (start_file = file, start_rank = rank;
         start_file < FILE_8 && start_rank > COL_A;
         start_file++, start_rank--);

    for (int i = start_file, j = start_rank;
         i >= FILE_1 && j <= COL_H;  i--, j++) {
         square to = {i, j};
         if ((i != file) && (board[i][j] == (QUEEN * not_turn) ||
             board[i][j] == (KING * not_turn)) &&
           (!bishop_attak_square(board, from, to))) {
            return true;
        }
    }

    return false;
}

int32_t bishop_evaluation(Board board, uint8_t file, uint8_t rank)
{
    int32_t eval = 0;
    int8_t turn = TURN(board, file, rank);

    eval += available_bishop_moves(board, file, rank);

    if (supported_bishop(board, file, rank) && 
        unexpulsable_bishop(board, file, rank)) {
        eval += UNEXPULSABLE_BISHOP_POND;
    }

    if (x_ray(board, file, rank)) {
        eval += BISHOP_X_RAY_POND;         
    }
    
    return eval * turn;
}

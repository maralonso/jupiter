#include <stdlib.h>
#include "board.h"
#include "pieces.h"
#include "generation.h"

static retval_t king_moves(Node_t *node, square sq, uint8_t file, uint8_t col)
{
    if (((abs(file - sq[0]) ==1) && (abs(col - sq[1])) <=1) ||
        ((abs(file - sq[0]) <=1) && (abs(col - sq[1])) ==1)) {

        if ((node->board[file][col] * node->turn) <= 0) {
            Move_t mov = {{sq[0], sq[1]}, {file, col}};
            SUCCES_OR_RETURN(insert_move(node, mov));
        }
    }
    return RV_SUCCESS;
}

static retval_t check_short_castle_squares(Node_t *node)
{
    uint8_t file = node->turn == WHITE ? FILE_1: FILE_8; 
    square f = {file, COL_F};
    square g = {file, COL_G};
    if (node->board[file][COL_E] == (KING * node->turn) &&
        node->board[file][COL_H] == (ROOK * node->turn) &&
        node->board[file][COL_F] == 0 &&
        node->board[file][COL_G] == 0 &&
        !square_attaked(node, f) && 
        !square_attaked(node, g)) {  
        
        return RV_SUCCESS;
    }   

    return RV_NO_MOVE_LEFT;
}

static retval_t check_long_castle_squares(Node_t *node)
{
    uint8_t file = node->turn == WHITE ? FILE_1: FILE_8; 
    square b = {file, COL_B};
    square c = {file, COL_C};
    square d = {file, COL_D};
    if (node->board[file][COL_E] == (KING * node->turn) && 
        node->board[file][COL_A] == (ROOK * node->turn) && 
        node->board[file][COL_B] == 0 &&
        node->board[file][COL_C] == 0 &&
        node->board[file][COL_D] == 0 &&
        !square_attaked(node, b) && 
        !square_attaked(node, c) && 
        !square_attaked(node, d)) {
        
        return RV_SUCCESS;

    }  

    return RV_NO_MOVE_LEFT;
}

static void king_castles(Node_t *node)
{
    if (node->castles & SHORT_CASTLES) {
        if (check_short_castle_squares(node) == RV_SUCCESS) {
            insert_castle(node, SHORT_CASTLES);   
        } 
    }
    if (node->castles & LONG_CASTLES) {
        if (check_long_castle_squares(node) == RV_SUCCESS) {
            insert_castle(node, LONG_CASTLES);   
        }
    }
}

retval_t get_king_moves(Node_t *node, square sq)
{
    if ((node->turn == WHITE && node->castles & W_CASTLES) || 
        (node->turn == BLACK && node->castles & B_CASTLES)) {
        king_castles(node); 
    }    

    uint8_t rotation = ROTATION_0 | ROTATION_90 | ROTATION_180 | ROTATION_270;
    return exec_with_rotation(node, sq, rotation, king_moves); 
}

int32_t king_evaluation(Board board, uint8_t file, uint8_t rank)
{
    //TODO
    return 0;
}

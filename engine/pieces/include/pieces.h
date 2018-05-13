#include "board.h"

#include <stdio.h>
#include <stdbool.h>

#define ROTATION_0     (1 << 0)
#define ROTATION_90    (1 << 1)
#define ROTATION_180   (1 << 2)
#define ROTATION_270   (1 << 3)

retval_t get_rook_moves(Node_t *node, square sq);
retval_t get_bishop_moves(Node_t *node, square sq);
retval_t get_knight_moves(Node_t *node, square sq);
retval_t get_king_moves(Node_t *node, square sq);
retval_t get_pawn_moves(Node_t *node, square sq);
retval_t get_queen_moves(Node_t *node, square sq);
bool pawn_attak_square(Board board, square from, square to);
bool rook_attak_square(Board board, square from, square to);
bool bishop_attak_square(Board bpard, square from, square to);
bool knight_attak_square(Board board, square from, square to);
bool queen_attak_square(Board board, square from, square to);

int32_t pawn_evaluation(Board board, uint8_t file, uint8_t rank);
int32_t rook_evaluation(Board board, uint8_t file, uint8_t rank);
int32_t knight_evaluation(Board board, uint8_t file, uint8_t rank);
int32_t bishop_evaluation(Board board, uint8_t file, uint8_t rank);
int32_t queen_evaluation(Board board, uint8_t file, uint8_t rank);
int32_t king_evaluation(Board board, uint8_t file, uint8_t rank);

typedef retval_t (*Eval_Whith_Rotation)(
        Node_t *node, 
        square sq, 
        uint8_t fil, 
        uint8_t col);


inline retval_t EXEC_ROTATE_0(Node_t *node, square sq, Eval_Whith_Rotation func)
{
    retval_t rv;

    for (int i = sq[0]; i <= FILE_8; i++) {
        for (int j = sq[1] + 1; j <= COL_H; j++) {
            rv = func(node,sq, i, j);
            SUCCES_OR_RETURN(rv);
        } 
    }
    return RV_SUCCESS;
}

inline retval_t EXEC_ROTATE_90(Node_t *node, square sq, Eval_Whith_Rotation func)
{
    retval_t rv;

    for (int i = sq[1]; i <= FILE_8; i++) {
        for (int j = sq[0] - 1; j >= COL_A; j--) {
            rv = func(node, sq, j, i);
            SUCCES_OR_RETURN(rv);
        } 
    } 
    return RV_SUCCESS;
}

inline retval_t EXEC_ROTATE_180(Node_t *node, square sq, Eval_Whith_Rotation func)
{
    retval_t rv;

    for (int i = sq[0]; i >= FILE_1; i--) {
        for (int j = sq[1] - 1; j >= COL_A; j--) {
            rv = func(node, sq, i, j);
            SUCCES_OR_RETURN(rv);
        } 
    } 
    return RV_SUCCESS;
}

inline retval_t EXEC_ROTATE_270(Node_t *node, square sq, Eval_Whith_Rotation func)
{
    retval_t rv;

    for (int i = sq[1]; i >= COL_A; i--) {
        for (int j = sq[0] + 1; j <= FILE_8; j++) {
            rv = func(node, sq, j, i);
            SUCCES_OR_RETURN(rv);
        } 
    } 
    return RV_SUCCESS;
}

inline retval_t exec_with_rotation(Node_t *node, square sq, 
                              uint8_t rotation, void *func)
{
    if (rotation & ROTATION_0) {
        EXEC_ROTATE_0(node, sq, func);
    }
    if (rotation & ROTATION_90) {
        EXEC_ROTATE_90(node, sq, func);
    }
    if (rotation & ROTATION_180) {
        EXEC_ROTATE_180(node, sq, func);
    }
    if (rotation & ROTATION_270) {
        EXEC_ROTATE_270(node, sq, func);
    }

    return RV_SUCCESS;
}

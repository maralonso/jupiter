#include <stdlib.h>
#include "board.h"
#include "pieces.h"
#include "generation.h"
#include "evaluation.h"

retval_t get_queen_moves(Node_t *node, square sq)
{
    retval_t rv;

    rv = get_rook_moves(node, sq);
    SUCCES_OR_RETURN(rv);

    return get_bishop_moves(node, sq);
}

bool queen_attak_square(Board board, square from, square to)
{
    return rook_attak_square(board, from, to) | bishop_attak_square(board, from, to);
}

int32_t queen_evaluation(Board board, uint8_t file, uint8_t rank)
{
    int32_t eval = 0;

    eval += rook_evaluation(board, file, rank);
    eval += bishop_evaluation(board, file, rank);

    return eval;
}

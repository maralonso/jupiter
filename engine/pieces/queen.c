#include <stdlib.h>
#include "board.h"
#include "pieces.h"
#include "generation.h"

retval_t get_queen_moves(Node_t *node, square sq)
{
    retval_t rv;

    rv = get_rook_moves(node, sq);
    SUCCES_OR_RETURN(rv);

    return get_bishop_moves(node, sq);
}

bool queen_attak_square(Node_t *node, square from, square to)
{
    return rook_attak_square(node, from, to) | bishop_attak_square(node, from, to);
}

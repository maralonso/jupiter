#ifndef _EVALUATION_H_
#define _EVALUATION_H_

#include "board.h"


#define ISOLATED_PAWN_POND          -40
#define PASSED_PAWN_POND            150
#define DOUBLED_PAWN_POND           -20
#define CONNECTED_ROOKS_POND        30
#define ROOK_X_RAY_POND             30
#define UNEXPULSABLE_BISHOP_POND    30
#define BISHOP_X_RAY_POND           30
#define KNIGHT_SUPOORTED_POND       30

int evaluate(Board board);

#endif

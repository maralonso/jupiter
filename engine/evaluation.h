#ifndef _EVALUATION_H_
#define _EVALUATION_H_

#include "board.h"


#define ISOLATED_PAWN_POND          -40
#define PASSED_PAWN_POND            20
#define DOUBLED_PAWN_POND           -20
#define CONNECTED_ROOKS_POND        30
#define ROOK_X_RAY_POND             30
#define UNEXPULSABLE_BISHOP_POND    30
#define BISHOP_X_RAY_POND           30
#define KNIGHT_SUPOORTED_POND       30

#define CENTER_CONTROL_POND         5
#define CENTER_CONTROL_C4_POND      5
#define CENTER_CONTROL_C5_POND      5
#define CENTER_CONTROL_F4_POND      5
#define CENTER_CONTROL_F5_POND      5
#define CENTER_CONTROL_D4_POND      10
#define CENTER_CONTROL_D5_POND      10
#define CENTER_CONTROL_E4_POND      10
#define CENTER_CONTROL_E5_POND      10

int32_t evaluate(Board board);

#endif

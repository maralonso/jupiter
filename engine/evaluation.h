#ifndef _EVALUATION_H_
#define _EVALUATION_H_

#include "board.h"


#define ISOLATED_PAWN_POND  -40
#define PASSED_PAWN_POND    150
#define DOUBLED_PAWN_POND   -20


int evaluate(Board board);

#endif

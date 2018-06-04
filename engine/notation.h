#ifndef _NOTATION_H_
#define _NOTATION_H_

#include "board.h"


retval_t get_move_from_notation(Move_t *mov, char *not);
retval_t get_notation_from_move(Move_t *mov, char *not);
#endif

#ifndef _GENERATION_H_
#define _GENERATION_H_

#include "board.h"

retval_t move_init(Node_t **node);
retval_t get_moves(Node_t *node);
retval_t insert_move(Node_t *parent, Move_t move);
retval_t insert_promotion(Node_t *parent, Move_t move);

#endif

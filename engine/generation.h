#ifndef _GENERATION_H_
#define _GENERATION_H_

#include "board.h"
#include <stdbool.h>

retval_t move_init(Node_t **node);
retval_t make_move(Node_t *node, Move_t mov);
retval_t get_moves(Node_t *node);
retval_t insert_move(Node_t *parent, Move_t move);
retval_t insert_promotion(Node_t *parent, Move_t move);
retval_t insert_castle(Node_t * parent, uint8_t castle);
retval_t insert_passant(Node_t *parent, Move_t move);
bool square_attaked(Node_t *node, square sq);

#endif

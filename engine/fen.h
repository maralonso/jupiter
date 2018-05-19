#ifndef _FEN_H_
#define _FEN_H_

#include "board.h"

#define MAX_FEN_LEN (sizeof("rnbkqbnr/pppppppp/00000000/00000000/00000000/00000000/PPPPPPPP/RNBKQBNR w KQwq e3 20 100 "))

retval_t get_fen_from_node(Node_t *node, char *fen);
retval_t get_node_from_fen(Node_t *node, char *fen);
#endif

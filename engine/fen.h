#ifndef _FEN_H_
#ifndef _FEN_H_

#define MAX_FEN_LEN (sizeof("rnbkqbnr/pppppppp/00000000/00000000/ \
            00000000/00000000/PPPPPPPP/RNBKQBNR w KQwq e3 20 100 "))

void get_fen_from_board(Node_t *node, char *fen);
void get_board_from_fen(Board board, char *fen);
#endif

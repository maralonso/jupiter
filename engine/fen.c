#include <stdint.h>
#include <stdio.h>
#include "board.h"


static char get_piece_name(int16_t square)
{
    switch(square) {
        case ROOK_W:
            return 'R';
        case ROOK_B:
            return 'r';
        case KNIGHT_W:
            return 'N';    
        case KNIGHT_B:
            return 'n';
        case BISHOP_W:
            return 'B';    
        case BISHOP_B: 
            return 'b';   
        case QUEEN_W:
            return 'Q';
        case QUEEN_B:
            return 'q';
        case KING_W:
            return 'K';
        case KING_B:
            return 'k';
        case PAWN_W:
            return 'P';
        case PAWN_B:
            return 'p';
        default:
            return '?';    
    }
}

static char* set_fen_castles(Node_t *node, char *fen)
{
    if (node->castles & W_CASTLES) {
        if (node->castles & W_SHORT_CASTLE) {
            *fen++ = 'K';
        }
        if (node->castles & W_LONG_CASTLE) {
            *fen++ = 'Q';
        }
    }else {
        *fen++ = '-';
    }

    if (node->castles & B_CASTLES) {
        if (node->castles & B_SHORT_CASTLE) {
            *fen++ = 'k';
        }
        if (node->castles & B_LONG_CASTLE) {
            *fen++ = 'q';
        }
    }else {
        *fen++ = '-';
    }

    *fen++ = ' ';

    return fen;
}

void get_fen_from_board(Node_t *node, char *fen)
{
    for (int i=8; i >= 0; i--) {
        for (int j=0; j < 8; j++) {
           if (node->board[i][j] != 0) {
              *fen++ = get_piece_name(node->board[i][j]);
           }
           else {
               int zeros = 0;
               while(node->board[i][j] == 0 && j < 8) {
                   zeros++;
                   j++;
               }
               *fen++ = 0x30 + zeros; //0x30 = 0
            }
        }
        if (i > 0) {
            *fen++ = '/';
        }else {
            *fen++ = ' ';
        }
    }

    *fen++ = node->turn == WHITE? 'w':'b';
    fen = set_fen_castles(node, fen);

    if (node->passant) {
       *fen++ = 0x61 + node->passant; // 0x61 = 'a'
       
    }else {
        *fen++ = '-';
    }

    fen += sprintf(fen, "%d ",node->half_moves);
    fen += sprintf(fen, "%d ",node->moves);
}

void get_board_from_fen(Board board, char *fen)
{
    
}

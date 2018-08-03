#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "board.h"
#include "fen.h"


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

static retval_t fill_board(Node_t *node, char **fen)
{
    int rank = 7;
    int file = 0;

    while (rank > 0 || file < 8) {
        switch (**fen) {
            case '/':
                rank--;
                file = 0;
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                file += atoi(*fen); 
                break;    
            case 'r':
                node->board[rank][file] = ROOK_B;
                file++;
                break;    
            case 'R':
                node->board[rank][file] = ROOK_W;
                file++;
                break;    
            case 'n':
                node->board[rank][file] = KNIGHT_B;
                file++;
                break;    
            case 'N':
                node->board[rank][file] = KNIGHT_W;
                file++;
                break;    
            case 'b':
                node->board[rank][file] = BISHOP_B;
                file++;
                break;    
            case 'B':
                node->board[rank][file] = BISHOP_W;
                file++;
                break;    
            case 'k':
                node->board[rank][file] = KING_B;
                file++;
                break;    
            case 'K':
                node->board[rank][file] = KING_W;
                file++;
                break;    
            case 'q':
                node->board[rank][file] = QUEEN_B;
                file++;
                break;    
            case 'Q':
                node->board[rank][file] = QUEEN_W;
                file++;
                break;    
            case 'p':
                node->board[rank][file] = PAWN_B;
                file++;
                break;    
            case 'P':        
                node->board[rank][file] = PAWN_W;
                file++;
                break;    
            default:
                return RV_ERROR;    
        }
        (*fen)++;
    } 
    (*fen)++;

    return RV_SUCCESS;
}

static retval_t get_node_turn(Node_t *node, char **fen)
{
    if (**fen == 'w') {
        node->turn = WHITE;
    }else if (**fen == 'b') {
        node->turn = BLACK;
    }else {
        return RV_ERROR;
    }
    (*fen) += 2;

    return RV_SUCCESS;
}

static retval_t get_node_castles(Node_t *node, char **fen)
{
    node->castles = 0;

    while(**fen != ' ') {
        switch (**fen) {
            case 'Q':
                node->castles |= W_LONG_CASTLE; 
            case 'q':
                node->castles |= B_LONG_CASTLE; 
            case 'K':
                node->castles |= W_SHORT_CASTLE; 
            case 'k':
                node->castles |= B_SHORT_CASTLE; 
            case '-':
                break;
            default:
            return RV_ERROR;
        }
        (*fen)++;
    }    
    (*fen)++;

    return RV_SUCCESS;
}

static retval_t get_node_passant(Node_t *node, char **fen)
{
    node->passant = NO_PASSANT;
    if (**fen != '-') {
        if (**fen < 'a' || **fen > 'h') {
            return RV_ERROR;
        }
        node->passant = **fen - 'a';
    }
    (*fen)++;

    return RV_SUCCESS;
}

static retval_t get_node_moves(Node_t *node, char **fen)
{
    char *token = " ";
    char *half_moves = strtok(*fen, token);
    char *moves = strtok(NULL, token);
    
    if (half_moves == NULL || moves == NULL) {
        return RV_ERROR;
    }

    node->half_moves = atoi(half_moves);
    node->moves = atoi(moves);

    return RV_SUCCESS;
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

static retval_t set_fen_pieces(Node_t *node, char **fen)
{
    for (int i=7; i >= 0; i--) {
        for (int j=0; j < 8; j++) {
           if (node->board[i][j] != 0) {
              **fen = get_piece_name(node->board[i][j]);
              (*fen)++;
           }
           else {
               int zeros = 0;
               while(node->board[i][j] == 0 && j < 8) {
                   zeros++;
                   j++;
               }
               **fen = 0x30 + zeros; //0x30 = 0
              (*fen)++;
              j--;
            }
        }
        if (i > 0) {
            **fen = '/';
            (*fen)++;
        }else {
            **fen = ' ';
            (*fen)++;
        }
    }

    return RV_SUCCESS;
}

retval_t get_fen_from_node(Node_t *node, char *fen)
{
    retval_t rv;
    char buffer[MAX_FEN_LEN] = {0};
    char *buff = buffer;

    memset(buffer, 0x0, MAX_FEN_LEN);

    rv = set_fen_pieces(node, &buff);
    SUCCES_OR_RETURN(rv);

    *buff++ = node->turn == WHITE? 'w':'b';
    *buff++ = ' ';
     buff = set_fen_castles(node, buff);

    if (node->passant != NO_PASSANT) {
       *buff++ = 0x61 + node->passant; // 0x61 = 'a'
       
    }else {
        *buff++ = '-';
    }
    *buff++ = ' ';

    buff += sprintf(buff, "%d ",node->half_moves);
    buff += sprintf(buff, "%d",node->moves);

    memcpy(fen, buffer, strlen(buffer) + 1);
    return RV_SUCCESS;
}

retval_t get_node_from_fen(Node_t *node, char *fen)
{
    retval_t rv; 
    memset(&node->board, 0x0, sizeof(node->board));

    rv = fill_board(node, &fen);
    SUCCES_OR_RETURN(rv); 

    rv = get_node_turn(node, &fen);
    SUCCES_OR_RETURN(rv);

    rv = get_node_castles(node, &fen);
    SUCCES_OR_RETURN(rv);

    rv = get_node_passant(node, &fen);
    SUCCES_OR_RETURN(rv);

    rv = get_node_moves(node, &fen);
    SUCCES_OR_RETURN(rv);

    return RV_SUCCESS;
}

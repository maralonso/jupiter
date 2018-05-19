#include "board.h"
#include "node.h"
#include "pieces.h"
#include <string.h>
#include <stdbool.h>

extern  retval_t WALK_BOARD(Node_t *node, Walk_Function func, square to);

static void copy_initial_board(Board *board)
{
    memcpy(board, initial_board, sizeof(initial_board));
}

static Node_t* create_move(void)
{
    Node_t *new = create_node();
    if (new == NULL) {
        return NULL;
    }

    new->child  = NULL;
    new->next   = NULL;
    new->parent = NULL;

    new->value  = 0;

    new->check_status = 0;   //TODO
    new->castles      = 0;   //TODO
    strcpy(new->notation, ""); //TODO

    return new;
}

static retval_t get_piece_moves(Node_t *node, uint8_t rank, uint8_t file, square to)
{
    retval_t rv = RV_SUCCESS;
    square from = {file, rank};
    switch(node->board[file][rank] * node->turn) {
        case PAWN:
            rv = get_pawn_moves(node, from);
            break;
        case ROOK:
            rv = get_rook_moves(node, from);
            break;
        case KNIGHT:
            rv = get_knight_moves(node, from);
            break;
        case BISHOP:
            rv = get_bishop_moves(node, from);
            break;
        case QUEEN:
            rv = get_queen_moves(node, from);
            break;
        case KING:
            rv = get_king_moves(node, from);
            break;
        default:
            break;
    }

    return rv;
}

static retval_t check_square_safe(Node_t *node, uint8_t rank, uint8_t file, square to)
{
    bool attaked;
    square from = {file, rank};
    
    switch(node->board[file][rank] * node->turn * -1) {
        case PAWN:
            attaked = pawn_attak_square(node->board, from, to);
            break;
        case ROOK:
            attaked = rook_attak_square(node->board, from, to);
            break;
        case KNIGHT:
            attaked = knight_attak_square(node->board, from, to);
            break;
        case BISHOP:
            attaked = bishop_attak_square(node->board, from, to);
            break;
        case QUEEN:
            attaked = queen_attak_square(node->board, from, to); 
            break;
        default:
            attaked = false;
            break;
    }

    if (attaked) {
        return RV_NO_MOVE_LEFT;
    }

    return RV_SUCCESS;
}

static retval_t new_promotion(Node_t *parent, Move_t move, int16_t piece)
{
    Node_t *new = create_move();
    if (new == NULL) {
        return RV_NO_MEMORY;
    }

    new->turn   = parent->turn * -1;
    new->castles = parent->castles;
    memcpy(&new->board, &parent->board, sizeof(Board));

    new->board[move.from[0]][move.from[1]] = 0;
    new->board[move.to[0]][move.to[1]] = piece;

    insert_node(parent, new);

    return RV_SUCCESS;
}

static void clear_castle(Node_t *node, Move_t move)
{
    uint8_t castles = node->turn == WHITE ? B_CASTLES: W_CASTLES;
    switch (move.from[1]) {
        case COL_E:
            break;
        case COL_A:
            castles &= LONG_CASTLES;
            break;
        case COL_H:
            castles &= SHORT_CASTLES;
            break;
        default:
            return;    
    }

    node->castles &= ~castles;
}

retval_t make_move(Node_t *node, Move_t mov)
{
    node->board[mov.to[0]][mov.to[1]] = node->board[mov.from[0]][mov.from[1]];
    node->board[mov.from[0]][mov.from[1]] = 0;

    node->turn = node->turn * -1;
    node->half_moves++;
    if (node->turn == WHITE) {
        node->moves++;
    }

    return RV_SUCCESS;
}

retval_t move_init(Node_t **node)
{
    if (node == NULL) {
        return RV_ERROR;
    }

    Node_t *new_node = create_node();
    if (new_node == NULL) {
        return RV_NO_MEMORY;
    }
    
    copy_initial_board(&new_node->board);
    strcpy(new_node->notation, "");

    new_node->value         = 0;
    new_node->turn          = WHITE;
    new_node->check_status  = NOT_CHECK;
    new_node->castles       = ALL_CASTLES;
    new_node->passant       = NO_PASSANT;

    new_node->child         = NULL;
    new_node->next          = NULL;
    new_node->parent        = NULL;

    *node = new_node;
    return RV_SUCCESS;
}

retval_t get_moves(Node_t *node)
{
    return WALK_BOARD(node, get_piece_moves, NULL);
}

retval_t insert_move(Node_t *parent, Move_t move)
{
    if (parent == NULL) {
        return RV_ERROR;
    }

    Node_t *new = create_move();
    if (new == NULL) {
        return RV_NO_MEMORY;
    }

    new->turn   = parent->turn * -1;
    new->castles = parent->castles;
    memcpy(&new->board, &parent->board, sizeof(Board));

    int16_t aux = new->board[move.from[0]][move.from[1]];
    if (aux == (ROOK * parent->turn) || aux == (KING * parent->turn)) {
        clear_castle(new, move);
    }

    new->board[move.from[0]][move.from[1]] = 0;
    new->board[move.to[0]][move.to[1]] = aux;
    insert_node(parent, new);

    return RV_SUCCESS;
}

retval_t insert_promotion(Node_t *parent, Move_t move)
{
    retval_t rv;

    rv = new_promotion(parent, move, QUEEN * parent->turn);
    SUCCES_OR_RETURN(rv);

    rv = new_promotion(parent, move, KNIGHT * parent->turn);
    SUCCES_OR_RETURN(rv);

    rv = new_promotion(parent, move, BISHOP * parent->turn);
    SUCCES_OR_RETURN(rv);

    return RV_SUCCESS;
}

retval_t insert_castle(Node_t * parent, uint8_t castle)
{
    if (parent == NULL) {
        return RV_ERROR;
    }

    Node_t *new = create_move();
    if (new == NULL) {
        return RV_NO_MEMORY;
    }

    new->turn   = parent->turn * -1;
    memcpy(&new->board, &parent->board, sizeof(Board));

    uint8_t file = parent->turn == WHITE ? FILE_1: FILE_8;
    uint8_t rook = castle & SHORT_CASTLES ? COL_H: COL_A;
    uint8_t new_rook = castle & SHORT_CASTLES ? COL_F: COL_D;
    uint8_t new_king = castle & SHORT_CASTLES ? COL_G: COL_C;

    new->board[file][new_rook] = new->board[file][rook];
    new->board[file][new_king] = new->board[file][COL_E];
    new->board[file][COL_E] = 0;
    new->board[file][rook] = 0;
    new->board[file][rook] = 0;
    new->board[file][rook] = 0;
    
    insert_node(parent, new);

    return RV_SUCCESS;
}

bool square_attaked(Node_t *node, square sq)
{
    return WALK_BOARD(node,check_square_safe, sq) != RV_SUCCESS;
}

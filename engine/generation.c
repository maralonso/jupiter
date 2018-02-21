#include "board.h"
#include "node.h"
#include <string.h>

extern  retval_t EVALUATE_BOARD(Node_t *node, Evaluation_Function func);

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

static retval_t get_piece_moves(Node_t *node, uint8_t rank, uint8_t file)
{
    switch(node->board[rank][file] * node->turn) {
        case PAWN:
            break;
        case ROOK:
            break;
        case KNIGHT:
            break;
        case BISHOP:
            break;
        case QUEEN:
            break;
        case KING:
            break;
        default:
            break;
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
    memcpy(&new->board, &parent->board, sizeof(Board));

    new->board[move.from[0]][move.from[1]] = 0;
    new->board[move.to[0]][move.to[1]] = piece;

    insert_node(parent, new);

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
    new_node->passant       = 0;

    new_node->child         = NULL;
    new_node->next          = NULL;
    new_node->parent        = NULL;

    *node = new_node;
    return RV_SUCCESS;
}

retval_t get_moves(Node_t *node)
{
    return EVALUATE_BOARD(node, get_piece_moves);
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
    memcpy(&new->board, &parent->board, sizeof(Board));

    int16_t aux = new->board[move.from[0]][move.from[1]];
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

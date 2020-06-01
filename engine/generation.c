#include "board.h"
#include "node.h"
#include "pieces.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "evaluation.h"
#include "notation.h"
#include <omp.h>

extern  retval_t WALK_BOARD(Node_t *node, Walk_Function func, square to);

bool _is_on_check(Node_t *node, int8_t color);

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

static retval_t new_promotion(Node_t *parent, Move_t move, int16_t piece, char c)
{
    Node_t *new = create_move();
    if (new == NULL) {
        return RV_NO_MEMORY;
    }

    new->turn   = parent->turn * -1;
    new->castles = parent->castles;
    new->passant = NO_PASSANT;
    memcpy(&new->board, &parent->board, sizeof(Board));
    new->board[move.from[0]][move.from[1]] = 0;
    new->board[move.to[0]][move.to[1]] = piece;

    if (_is_on_check(new, parent->turn)) {
        delete_node(new);
        return RV_ERROR;
    }

    new->value = evaluate(new->board); 
    get_notation_from_move(&move, new->notation);
    new->notation[4] = c;
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

static void make_castle(Node_t *node, Move_t mov)
{
    uint8_t rook_from = mov.to[1] == COL_G? COL_H: COL_A;
    uint8_t rook_to = mov.to[1] == COL_G? COL_F: COL_D;

    node->board[mov.from[0]][rook_to] = node->board[mov.from[0]][rook_from];
    node->board[mov.from[0]][rook_from] = 0;
}

static void make_passant(Node_t *node, Move_t mov)
{
    node->board[mov.from[0]][mov.to[1]] = 0;
}

static void make_promotion(Node_t *node, Move_t mov)
{
    int8_t turn = TURN(node->board, mov.from[0], mov.from[1]);
    node->board[mov.from[0]][mov.from[1]] = 0;
    int16_t piece = 0;
    
    switch (mov.to[0]) {
        case PROMOTION_QUEEN:
            piece = QUEEN * turn;
            break;
        case PROMOTION_BISHOP:
            piece = BISHOP * turn;
            break;
        case PROMOTION_KNIGHT:
            piece = KNIGHT * turn;
            break;
        case PROMOTION_ROOK:
            piece = ROOK * turn;
            break;
    }

    node->turn = node->turn * -1;
    node->half_moves++;
    if (node->turn == WHITE) {
        node->moves++;
    }
  
    node->board[mov.from[0] + turn][mov.to[1]] = piece;
}

retval_t make_move(Node_t *node, Move_t mov)
{
    if (mov.to[0] & PROMOTION_MASK) {
        make_promotion(node, mov);
        return RV_SUCCESS;
    }

    if (node->board[mov.from[0]][mov.from[1]] == KING * node->turn &&
        abs(mov.from[1] - mov.to[1]) > 1) {
        make_castle(node, mov);
    }

    if (node->board[mov.from[0]][mov.from[1]] == PAWN * node->turn &&
        mov.from[1] != mov.to[1] &&
        node->board[mov.to[0]][mov.to[1]] == 0) {
        make_passant(node, mov);
    }

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
    new->passant = NO_PASSANT;
    memcpy(&new->board, &parent->board, sizeof(Board));

    int16_t aux = new->board[move.from[0]][move.from[1]];
    if (aux == (ROOK * parent->turn) || aux == (KING * parent->turn)) {
        clear_castle(new, move);
    }

    if (aux == (PAWN * parent->turn) && abs(move.from[0] - move.to[0]) > 1) {
        new->passant = move.from[1];
    }

    new->board[move.from[0]][move.from[1]] = 0;
    new->board[move.to[0]][move.to[1]] = aux;
    
    if (_is_on_check(new, parent->turn)) {
        delete_node(new);
        return RV_ERROR;
    }

    get_notation_from_move(&move, new->notation);
    new->value = evaluate(new->board);
    insert_node(parent, new);
    return RV_SUCCESS;
}

retval_t insert_promotion(Node_t *parent, Move_t move)
{
    retval_t rv;

    rv = new_promotion(parent, move, QUEEN * parent->turn, 'q');
    SUCCES_OR_RETURN(rv);

    rv = new_promotion(parent, move, KNIGHT * parent->turn, 'n');
    SUCCES_OR_RETURN(rv);

    rv = new_promotion(parent, move, BISHOP * parent->turn, 'b');
    SUCCES_OR_RETURN(rv);

    rv = new_promotion(parent, move, ROOK * parent->turn, 'r');
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
    new->castles = parent->castles;
    new->passant = NO_PASSANT;
    memcpy(&new->board, &parent->board, sizeof(Board));

    uint8_t file = parent->turn == WHITE ? FILE_1: FILE_8;
    uint8_t rook = castle & SHORT_CASTLES ? COL_H: COL_A;
    uint8_t new_rook = castle & SHORT_CASTLES ? COL_F: COL_D;
    uint8_t new_king = castle & SHORT_CASTLES ? COL_G: COL_C;
    Move_t mov = {
       .from = {file, rook},
       .to = {file, new_rook},
    };
    clear_castle(new, mov);
    new->board[file][new_rook] = new->board[file][rook];
    new->board[file][new_king] = new->board[file][COL_E];
    new->board[file][COL_E] = 0;
    new->board[file][rook] = 0;
    new->board[file][rook] = 0;
    new->board[file][rook] = 0;
    
    if (_is_on_check(new, parent->turn)) {
        delete_node(new);
        return RV_ERROR;
    }

    new->value = evaluate(new->board); 
    Move_t move = {{file, COL_E}, {file, new_king}};
    get_notation_from_move(&move, new->notation);

    insert_node(parent, new);
    return RV_SUCCESS;
}

retval_t insert_passant(Node_t *parent, Move_t move)
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
    new->passant = NO_PASSANT;
    memcpy(&new->board, &parent->board, sizeof(Board));

    int16_t aux = new->board[move.from[0]][move.from[1]];

    new->board[move.from[0]][move.from[1]] = 0;
    new->board[move.to[0]][move.to[1]] = aux;
    make_passant(new, move);

    if (_is_on_check(new, parent->turn)) {
        delete_node(new);
        return RV_ERROR;
    }

    get_notation_from_move(&move, new->notation);
    new->value = evaluate(new->board);
    insert_node(parent, new);
    return RV_SUCCESS;

}

bool square_attaked(Node_t *node, square sq)
{
    return WALK_BOARD(node,check_square_safe, sq) != RV_SUCCESS;
}

retval_t _get_king_position(Node_t *node, int8_t color, square *sq)
{
    for (int i = FILE_1; i <= FILE_8; i++) {
        for (int j = COL_A; j <= COL_H; j++) {
            if (node->board[i][j] == (KING * color)) {
                sq[0][0] = i;
                sq[0][1] = j;
                return RV_SUCCESS;
            }
        }
    }
    return RV_ERROR;
}

bool _is_on_check(Node_t *node, int8_t color)
{
    retval_t rv;
    square sq;

    rv = _get_king_position(node, color, &sq);

    if (rv == RV_SUCCESS) {
        node->turn *= -1;
        bool r = square_attaked(node, sq);
        node->turn *= -1;
        return r;
    } else {
        return false;
    }
}

static void generate_nodes(Node_t *node)
{
    Node_t *aux = node;

    while(aux != NULL) {
        if (aux->child != NULL) {
            generate_nodes(aux->child);
        } else { 
            get_moves(aux);
        }
        aux = aux->next;
    }
}

static int get_node_childs(Node_t *node)
{
    Node_t *aux;
    int count = 0;
    if (node->child != NULL) {
        aux = node->child;
        while (aux != NULL) {
            count++;
            aux = aux->next;
        }
    }

    return count;
}

void generate(Node_t *node)
{
    int node_childs = get_node_childs(node);

    if (node_childs == 0) {
        generate_nodes(node);
    } else {
        #pragma  omp parallel
        {
            #pragma omp for schedule(guided, 5)
            for (int i=0; i < node_childs; i++) {
                Node_t *child = node->child;
                for (int j=0; j < i; j++) {
                        child = child->next;
                }
                if (child->child != NULL) {
                    generate_nodes(child->child);
                } else {
                    get_moves(child);
                }
            }
        }
    }
}


#ifndef _BOARD_H
#define _BOARD_H

#include <stdint.h>


/**
 * Squares
 **/
#define COL_A	0
#define COL_B	1
#define COL_C	2
#define COL_D	3
#define COL_E	4
#define COL_F	5
#define COL_G	6
#define COL_H	7

#define FILE_1	0
#define FILE_2	1
#define FILE_3	2
#define FILE_4	3
#define FILE_5	4
#define FILE_6	5
#define FILE_7	6
#define FILE_8	7



/**
 * Pieces  Values  
 **/
#define BLACK			-1
#define WHITE			1

#define	PAWN	 		100
#define	KNIGHT			310
#define	BISHOP			315
#define	ROOK			500
#define	QUEEN			900
#define	KING			20000

#define	PAWN_B			(PAWN * BLACK)
#define	KNIGHT_B		(KNIGHT * BLACK)
#define	BISHOP_B		(BISHOP * BLACK)
#define	ROOK_B			(ROOK * BLACK)
#define	QUEEN_B			(QUEEN * BLACK)
#define	KING_B			(KING * BLACK)

#define	PAWN_W			(PAWN * WHITE)
#define	KNIGHT_W		(KNIGHT * WHITE)
#define	BISHOP_W		(BISHOP * WHITE)
#define	ROOK_W			(ROOK * WHITE)
#define	QUEEN_W			(QUEEN * WHITE)
#define	KING_W			(KING * WHITE)


/**
 * Special Moves
 **/
#define SHORT_CASTLE				10
#define LONG_CASTLE   				100
#define PROMOTION					50

#define W_SHORT_CASTLE_BIT			0X01
#define W_LONG_CASTLE_BIT   		0X02
#define B_SHORT_CASTLE_BIT			0X04
#define B_LONG_CASTLE_BIT   		0X08

#define ALL_CASTLES ( \
        W_SHORT_CASTLE_BIT | \
        W_LONG_CASTLE_BIT  | \
        B_SHORT_CASTLE_BIT | \
        B_LONG_CASTLE_BIT )

#define TURN(x,y)	((x[y[0]][y[1]] > 0) ? WHITE: BLACK)


typedef int8_t  square[2];
typedef int16_t  Board[8][8];


typedef enum {
    RV_SUCCESS = 0,
    RV_ERROR,
    RV_NO_MOVE_LEFT,
    RV_NO_MEMORY,
} retval_t;

#define SUCCES_OR_RETURN(_rv_)  {retval_t __rv = _rv_; if (RV_SUCCESS != __rv) return __rv;}

/**
 *
 **/ 
typedef struct {
	square from;
	square to;
} Move_t;

typedef enum {
    NOT_CHECK,
    CHECK,
    CHECK_MATE,
} check_status_t;


/**
 *
 **/ 
struct Node {
    //Move_t mov;
	Board board;
	char notation[10];
	int value;

	int8_t  turn;
	check_status_t  check_status;

	int8_t castles;
    int8_t passant;
	
	struct Node  *child;
	struct Node  *next;
	struct Node  *parent;
};

typedef struct Node Node_t;

/**
 *
 **/
typedef retval_t (*Evaluation_Function) (Node_t *node, uint8_t rank, uint8_t file);
inline retval_t EVALUATE_BOARD(Node_t *node, Evaluation_Function func)
{
    retval_t rv;
    for(int i = FILE_1; i <= FILE_8; i++) {
        for(int j = COL_A; j <= COL_H; j++) {
            rv = func(node, i , j);
            SUCCES_OR_RETURN(rv);
        }
    }
    return RV_SUCCESS;
}

static const Board initial_board = {
    {ROOK_W, KNIGHT_W, BISHOP_W, QUEEN_W, KING_W, BISHOP_W, KNIGHT_W, ROOK_W},
    {PAWN_W, PAWN_W, PAWN_W, PAWN_W, PAWN_W, PAWN_W, PAWN_W, PAWN_W},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {PAWN_B, PAWN_B, PAWN_B, PAWN_B, PAWN_B, PAWN_B, PAWN_B, PAWN_B},
    {ROOK_B, KNIGHT_B, BISHOP_B, QUEEN_B, KING_B, BISHOP_B, KNIGHT_B, ROOK_B}
};

#define DEBUG

#ifdef DEBUG
#define DBG(x...) printf(x)
#else
#define DBG(x...) 
#endif


#endif

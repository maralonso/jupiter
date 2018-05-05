#include "generation.h"
#include "board.h"
#include "fen.h"
#include "cu/cu.h"
#include "stdio.h"
#include "node.h"

#include <string.h>

static char fen[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0";

TEST(test_fen_get_board)
{
    retval_t rv;
    Node_t node;

    rv = get_node_from_fen(&node, fen);     
    assertEquals(rv, RV_SUCCESS);

    for (int i=0; i < 8; i++) {
        for (int j=0; j < 8; j++) {
            assertEquals(node.board[i][j], initial_board[i][j]);     
        }
    }    

    assertEquals(node.turn, WHITE);
    assertEquals(node.passant, NO_PASSANT);
    assertEquals(node.moves, 0);
    assertEquals(node.half_moves, 0);
    assertEquals(node.castles, ALL_CASTLES);
}


TEST(test_fen_get_board_moves)
{
    char test_fen[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w QKqk - 25 100";
    retval_t rv;
    Node_t node;

    rv = get_node_from_fen(&node, test_fen);     
    assertEquals(rv, RV_SUCCESS);

    assertEquals(node.moves, 100);
    assertEquals(node.half_moves, 25);
}

TEST(test_fen_get_fen)
{
    retval_t rv;
    Node_t *node;
    char test_fen[MAX_FEN_LEN];
    memset(test_fen, 0x0, MAX_FEN_LEN);

    rv = move_init(&node);
    assertEquals(rv, RV_SUCCESS);

    rv = get_fen_from_node(node, test_fen);
    assertEquals(rv, RV_SUCCESS);

    for (int i=0; i < strlen(fen); i++) {
        assertEquals(fen[i], test_fen[i]);
    }
}

#include "board.h"
#include "generation.h"
#include "cu/cu.h"
#include "stdio.h"
#include "node.h"
#include <string.h>
#include <stdio.h>
#include "fen.h"
#include "notation.h"
#include "engine.h"


TEST(test_move_init)
{
    Node_t *node;
    retval_t rv;
    rv = move_init(&node);
    
    assertEquals(rv, RV_SUCCESS);
    assertEquals(node->value, 0);
    assertEquals(node->turn, WHITE);
    assertEquals(node->check_status, NOT_CHECK);
    assertEquals(node->castles, ALL_CASTLES);
    assertEquals(node->passant, NO_PASSANT);
    assertEquals(node->child, NULL);
    assertEquals(node->next, NULL);
    assertEquals(node->parent, NULL);
    
    int i,j;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            assertEquals(node->board[i][j], initial_board[i][j]);
        }
    }
}

TEST(test_node_init_fail)
{
    retval_t rv;

    rv = move_init(NULL);
    assertEquals(rv, RV_ERROR);
}

TEST(test_insert_move)
{
    uint32_t count;
    Node_t *node;
    retval_t rv;
    rv = move_init(&node);
    assertEquals(rv, RV_SUCCESS);

    Move_t mov = {{0, 0}, {0,0}};
    rv = insert_move(node, mov);
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 2);

    rv = insert_move(node, mov);
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 3);

    rv = insert_move(node, mov);
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(count, 4);

    //TODO Check Node fields
}

TEST(test_insert_move_fail)
{
    Move_t mov = {{0, 0}, {0,0}};
    retval_t rv = insert_move(NULL, mov);
    assertEquals(rv, RV_ERROR);
} 

TEST(test_square_attaked)
{
    Node_t *node;
    move_init(&node);

    Board board = {
        {QUEEN_W, ROOK_W, 0, 0, 0, 0, 0, 0},
        {0, BISHOP_W, KNIGHT_W, 0, 0, 0, PAWN_W, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, BISHOP_B, KNIGHT_B, 0, 0, 0, PAWN_B, 0},
        {QUEEN_B, ROOK_B, 0, 0, 0, 0, 0,0}
    };

    node->turn = BLACK;
    memcpy(node->board, board, sizeof(Board));
    square sq1 = {FILE_7, COL_A};
    square sq2 = {FILE_1, COL_H};
    square sq3 = {FILE_7, COL_G};
    square sq4 = {FILE_3, COL_H};
    square sq5 = {FILE_4, COL_D};
    square sq11 = {FILE_5, COL_B};
    square sq21 = {FILE_8, COL_C};
    square sq31 = {FILE_3, COL_B};
    square sq41 = {FILE_2, COL_D};
    square sq51 = {FILE_8, COL_G};
    assertTrue(square_attaked(node, sq1)); 
    assertTrue(square_attaked(node, sq2)); 
    assertTrue(square_attaked(node, sq3)); 
    assertTrue(square_attaked(node, sq4)); 
    assertTrue(square_attaked(node, sq5)); 
    assertFalse(square_attaked(node, sq11)); 
    assertFalse(square_attaked(node, sq11)); 
    assertFalse(square_attaked(node, sq21)); 
    assertFalse(square_attaked(node, sq31)); 
    assertFalse(square_attaked(node, sq41)); 
    assertFalse(square_attaked(node, sq51)); 

    node->turn = WHITE;
    square sq6 = {FILE_1, COL_A};
    square sq7 = {FILE_8, COL_H};
    square sq8 = {FILE_2, COL_G};
    square sq9 = {FILE_6, COL_H};
    square sq10 = {FILE_5, COL_D};
    assertTrue(square_attaked(node, sq6)); 
    assertTrue(square_attaked(node, sq7)); 
    assertTrue(square_attaked(node, sq8)); 
    assertTrue(square_attaked(node, sq9)); 
    assertTrue(square_attaked(node, sq10)); 

}

TEST(test_clear_castles)
{
    Node_t *node;
    retval_t rv;
    move_init(&node);

    Board board = {
        {ROOK_W, 0, 0, 0, KING_W, 0, 0, ROOK_W},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {ROOK_B, 0, 0, 0, KING_B, 0, 0,ROOK_B}
    };

    memcpy(node->board, board, sizeof(Board));
    Move_t m1 = {{FILE_1, COL_H}, {FILE_2, COL_H}};
    Move_t m2 = {{FILE_1, COL_A}, {FILE_2, COL_A}};
    Move_t m3 = {{FILE_1, COL_E}, {FILE_2, COL_E}};

    rv = insert_move(node, m1);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(node->child->castles, (ALL_CASTLES & (~W_SHORT_CASTLE)));
    delete_node(node->child);

    node->castles = ALL_CASTLES;
    rv = insert_move(node, m2);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(node->child->castles, (ALL_CASTLES & (~W_LONG_CASTLE)));
    delete_node(node->child);
    
    node->castles = ALL_CASTLES;
    rv = insert_move(node, m3);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(node->child->castles, (ALL_CASTLES & (~W_CASTLES)));
    delete_node(node->child);
    
    node->turn = BLACK;
    node->castles = ALL_CASTLES;
    Move_t m4 = {{FILE_8, COL_H}, {FILE_7, COL_H}};
    Move_t m5 = {{FILE_8, COL_A}, {FILE_7, COL_A}};
    Move_t m6 = {{FILE_8, COL_E}, {FILE_7, COL_E}};

    rv = insert_move(node, m4);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(node->child->castles, (ALL_CASTLES & (~B_SHORT_CASTLE)));
    delete_node(node->child);
    
    node->castles = ALL_CASTLES;
    rv = insert_move(node, m5);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(node->child->castles, (ALL_CASTLES & (~B_LONG_CASTLE)));
    delete_node(node->child);
    
    node->castles = ALL_CASTLES;
    rv = insert_move(node, m6);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(node->child->castles, (ALL_CASTLES & (~B_CASTLES)));
    delete_node(node->child);
}

TEST(test_gen_moves)
{
    uint32_t count;
    Node_t *node;
    retval_t rv;
    rv = move_init(&node);
    assertEquals(rv, RV_SUCCESS);

    rv = get_moves(node);
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(21, count);
    
    rv = get_moves(node->child);
    assertEquals(rv, RV_SUCCESS);
    count = get_tree_count(node);
    assertEquals(41, count);
}

TEST(test_make_move)
{
    Node_t *node;
    retval_t rv;
    rv = move_init(&node);

    Move_t move = {{FILE_1, COL_B}, {FILE_3, COL_C}};
    rv = make_move(node, move);
    assertEquals(RV_SUCCESS, rv);
    assertEquals(KNIGHT_W, node->board[FILE_3][COL_C]);
    assertEquals(BLACK, node->turn);

    Move_t move2 = {{FILE_7, COL_D}, {FILE_5, COL_D}};
    rv = make_move(node, move2);
    assertEquals(RV_SUCCESS, rv);
    assertEquals(PAWN_B, node->board[FILE_5][COL_D]);
    assertEquals(WHITE, node->turn);
}

TEST(test_make_move_castle)
{
    Node_t node, node2, node3, node4;
    retval_t rv;
    char fen[] = "r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 0";        
    rv = get_node_from_fen(&node, fen);
    assertEquals(rv, RV_SUCCESS);

    Move_t move = {{FILE_1, COL_E}, {FILE_1, COL_G}};
    rv = make_move(&node, move);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(KING_W, node.board[FILE_1][COL_G]);
    assertEquals(0, node.board[FILE_1][COL_H]);
    assertEquals(0, node.board[FILE_1][COL_E]);
    assertEquals(ROOK_W, node.board[FILE_1][COL_F]);

    char fen2[] = "r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 0";        
    rv = get_node_from_fen(&node2, fen2);
    assertEquals(rv, RV_SUCCESS);

    Move_t move2 = {{FILE_1, COL_E}, {FILE_1, COL_C}};
    rv = make_move(&node2, move2);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(KING_W, node2.board[FILE_1][COL_C]);
    assertEquals(0, node2.board[FILE_1][COL_A]);
    assertEquals(0, node2.board[FILE_1][COL_E]);
    assertEquals(ROOK_W, node2.board[FILE_1][COL_D]);

    char fen3[] = "r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R b KQkq - 0 0";        
    rv = get_node_from_fen(&node3, fen3);
    assertEquals(rv, RV_SUCCESS);

    Move_t move3 = {{FILE_8, COL_E}, {FILE_8, COL_C}};
    rv = make_move(&node3, move3);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(KING_B, node3.board[FILE_8][COL_C]);
    assertEquals(0, node3.board[FILE_8][COL_A]);
    assertEquals(0, node3.board[FILE_8][COL_E]);
    assertEquals(ROOK_B, node3.board[FILE_8][COL_D]);

    char fen4[] = "r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R b KQkq - 0 0";        
    rv = get_node_from_fen(&node4, fen4);
    assertEquals(rv, RV_SUCCESS);

    Move_t move4 = {{FILE_8, COL_E}, {FILE_8, COL_G}};
    rv = make_move(&node4, move4);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(KING_B, node4.board[FILE_8][COL_G]);
    assertEquals(0, node4.board[FILE_8][COL_H]);
    assertEquals(0, node4.board[FILE_8][COL_E]);
    assertEquals(ROOK_B, node4.board[FILE_8][COL_F]);

}

TEST(test_make_move_passant)
{
    Node_t node, node2;
    retval_t rv;
    char fen[] = "8/8/8/4Pp2/8/8/8/8 w KQkq f6 0 0";        
    rv = get_node_from_fen(&node, fen);
    assertEquals(rv, RV_SUCCESS);

    Move_t move = {{FILE_5, COL_E}, {FILE_6, COL_F}};
    rv = make_move(&node, move);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(PAWN_W, node.board[FILE_6][COL_F]);
    assertEquals(0, node.board[FILE_5][COL_F]);
    assertEquals(0, node.board[FILE_5][COL_E]);
    
    char fen2[] = "8/8/8/8/4Pp2/8/8/8 b KQkq e3 0 0";        
    rv = get_node_from_fen(&node2, fen2);
    assertEquals(rv, RV_SUCCESS);

    Move_t move2 = {{FILE_4, COL_F}, {FILE_3, COL_E}};
    rv = make_move(&node2, move2);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(PAWN_B, node2.board[FILE_3][COL_E]);
    assertEquals(0, node2.board[FILE_4][COL_E]);
    assertEquals(0, node2.board[FILE_4][COL_F]);
}

TEST(test_passant_flag_is_set)
{
    uint64_t node_count;
    Node_t *node;
    char fen[] = "8/8/8/8/5p2/5P2/4P3/8 w - - 0 0";
    node = create_node();
    retval_t rv = get_node_from_fen(node, fen);
    assertEquals(rv, RV_SUCCESS);

    generate(node);
    node_count = perft(node);
    assertEquals(2, node_count);

    generate(node);
    node_count = perft(node);
    assertEquals(2, node_count);

    Node_t *node2;
    char fen2[] = "8/2p5/3p4/3P4/8/8/8/8 b - - 0 0";
    node2 = create_node();
    rv = get_node_from_fen(node2, fen2);
    assertEquals(rv, RV_SUCCESS);

    generate(node2);
    node_count = perft(node2);
    assertEquals(2, node_count);

    generate(node2);
    node_count = perft(node2);
    assertEquals(2, node_count);

}

TEST(test_make_move_promotion)
{
    Node_t node, node2;
    retval_t rv;
    char fen[] = "8/4P3/8/8/8/8/8/8 w KQkq f6 0 0";        
    rv = get_node_from_fen(&node, fen);
    assertEquals(rv, RV_SUCCESS);
    
    char not[] = "e7e8q";
    Move_t move;
    get_move_from_notation(&move, not);
    rv = make_move(&node, move);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(QUEEN_W, node.board[FILE_8][COL_E]);
    assertEquals(0, node.board[FILE_7][COL_E]);

    char fen2[] = "3RR3/4P3/8/8/8/8/8/8 w KQkq f6 0 0";        
    rv = get_node_from_fen(&node2, fen2);
    assertEquals(rv, RV_SUCCESS);
    
    char not2[] = "e7d8q";
    Move_t move2;
    get_move_from_notation(&move2, not2);
    rv = make_move(&node2, move2);
    assertEquals(rv, RV_SUCCESS);
    assertEquals(QUEEN_W, node2.board[FILE_8][COL_D]);
    assertEquals(0, node2.board[FILE_7][COL_E]);
}

TEST(test_perft_1)
{
    uint64_t node_count;
    Node_t *node;
    move_init(&node);
    
    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 20);

    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 400);

    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 8902);

    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 197281);
    delete_node(node);
}

TEST(test_perft_2)
{
    uint64_t node_count;
    Node_t *node;
    retval_t rv;
    node = create_node();

    char fen[] = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 0";
    rv = get_node_from_fen(node, fen);
    assertEquals(rv, RV_SUCCESS);
    
    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 48);

    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 2039);
    
    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 97862);

    /*
    generate(node);
    node_count = perft(node);
    printf("\nnode count %ld\n", node_count);
    assertEquals(node_count, 4085603);
    */
    delete_node(node);
}

TEST(test_perft_3)
{
    uint64_t node_count;
    Node_t *node;
    retval_t rv;
    node = create_node();

    char fen[] = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 0";
    rv = get_node_from_fen(node, fen);
    assertEquals(rv, RV_SUCCESS);
    
    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 14);

    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 191);
    
    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 2812);

    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 43238);
    
    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 674624);
    delete_node(node);
}

TEST(test_perft_4)
{
    uint64_t node_count;
    Node_t *node;
    retval_t rv;
    node = create_node();

    char fen[] = "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1";
    rv = get_node_from_fen(node, fen);
    assertEquals(rv, RV_SUCCESS);
    
    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 6);
    
    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 264);
    
    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 9467);

    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 422333);
    delete_node(node);
}

TEST(test_perft_5)
{
    uint64_t node_count;
    Node_t *node;
    retval_t rv;
    node = create_node();

    char fen[] = "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8";
    rv = get_node_from_fen(node, fen);
    assertEquals(rv, RV_SUCCESS);
    
    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 44);

    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 1486);
    
    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 62379);

    /*
    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 2103487);
    */
    delete_node(node);
}

TEST(test_perft_6)
{
    uint64_t node_count;
    Node_t *node;
    retval_t rv;
    node = create_node();

    char fen[] = "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10";
    rv = get_node_from_fen(node, fen);
    assertEquals(rv, RV_SUCCESS);
    
    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 46);

    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 2079);
    
    generate(node);
    node_count = perft(node);
    assertEquals(node_count, 89890);
    delete_node(node);
}

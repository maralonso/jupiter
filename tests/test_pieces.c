#include "board.h"
#include "stdio.h"
#include "generation.h"
#include "node.h"
#include "string.h"
#include "pieces/include/pieces.h"

#include "cu/cu.h"

static uint8_t call_count;

static retval_t testing_eval(Node_t *node, square sq, uint8_t file, uint8_t col)
{
    assertEquals(node->board[file][col], call_count);
    call_count++;
    return RV_SUCCESS;
}

TEST(test_rotate_0)
{
    Node_t *node;
    retval_t rv;
    rv = move_init(&node);
    assertEquals(rv, RV_SUCCESS);

    Board board = {
        {-1, 0, 1, 2, 3 ,4 ,5 ,6},
        {-1, 7, 8, 9,10,11, 12, 13},
        {-1, 14, 15, 16, 17, 18, 19, 20},
        {-1, 21, 22, 23, 24, 25, 26, 27},
        {-1, 28, 29, 30, 31, 32, 33, 34},
        {-1, 35, 36, 37, 38, 39, 40, 41},
        {-1 ,42, 43, 44, 45, 46, 47, 48},
        {-1, 49, 50, 51, 52, 53, 54, 55}};

    memcpy(node->board, board, sizeof(Board));

    call_count = 0;
    square sq = {FILE_1, COL_A};
    EXEC_ROTATE_0(node, sq, testing_eval);
    assertEquals(56, call_count);
}

TEST(test_rotate_90)
{
    Node_t *node;
    retval_t rv;
    rv = move_init(&node);
    assertEquals(rv, RV_SUCCESS);

    Board board = {
        {6, 13, 20, 27, 34, 41, 48, 55},
        {5, 12, 19, 26, 33, 40, 47, 54},
        {4, 11, 18, 25, 32, 39, 46, 53},
        {3, 10, 17, 24, 31, 38, 45, 52},
        {2, 9, 16, 23, 30, 37, 44, 51},
        {1, 8, 15, 22, 29, 36, 43, 50},
        {0, 7, 14, 21, 28, 35, 42, 49},
        {-1, -1, -1, -1, -1, -1, -1, -1}};

    memcpy(node->board, board, sizeof(Board));

    call_count = 0;
    square sq = {FILE_8, COL_A};
    EXEC_ROTATE_90(node, sq, testing_eval);
    assertEquals(56, call_count);
}

TEST(test_rotate_180)
{
    Node_t *node;
    retval_t rv;
    rv = move_init(&node);
    assertEquals(rv, RV_SUCCESS);

    Board board = {
        {55, 54, 53, 52, 51, 50, 49, -1},
        {48, 47, 46, 45, 44, 43, 42, -1},
        {41, 40, 39, 38, 37, 36, 35, -1},
        {34, 33, 32, 31, 30, 29, 28, -1},
        {27, 26, 25, 24, 23, 22, 21, -1},
        {20, 19, 18, 17, 16, 15, 14, -1},
        {13, 12, 11, 10, 9, 8, 7, -1},
        {6, 5, 4, 3, 2, 1, 0, -1}};


    memcpy(node->board, board, sizeof(Board));

    call_count = 0;
    square sq = {FILE_8, COL_H};
    EXEC_ROTATE_180(node, sq, testing_eval);
    assertEquals(56, call_count);
}

TEST(test_rotate_270)
{
    Node_t *node;
    retval_t rv;
    rv = move_init(&node);
    assertEquals(rv, RV_SUCCESS);

    Board board = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {49, 42, 35, 28, 21, 14, 7, 0},
        {50, 43, 36, 29, 22, 15, 8, 1},
        {51, 44, 37, 30, 23, 16, 9, 2},
        {52, 45, 38, 31, 24, 17, 10, 3},
        {53, 46, 39, 32, 25, 18, 11, 4},
        {54, 47, 40, 33, 26, 19, 12, 5},
        {55, 48, 41, 34, 27, 20, 13, 6}};

    memcpy(node->board, board, sizeof(Board));

    call_count = 0;
    square sq = {FILE_1, COL_H};
    EXEC_ROTATE_270(node, sq, testing_eval);
    assertEquals(56, call_count);
}

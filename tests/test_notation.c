#include "board.h"
#include "cu/cu.h"
#include "stdio.h"
#include <string.h>
#include <stdio.h>
#include "notation.h"


TEST(test_get_notation)
{
    Move_t mov;
    char notation[NOTATION_STR_LEN];

    mov.from[0] = FILE_1;
    mov.from[1] = COL_A;
    mov.to[0] = FILE_3;  
    mov.to[1] = COL_C;

    get_notation_from_move(&mov, notation);

    assertEquals(0, strncmp(notation, "a1c3", strlen("a1c3")));  
}

TEST(get_move)
{
    char notation[NOTATION_STR_LEN] = "f8g5";
    Move_t move;

    get_move_from_notation(&move, notation);

    assertEquals(move.from[0], FILE_8);
    assertEquals(move.from[1], COL_F);
    assertEquals(move.to[0], FILE_5);
    assertEquals(move.to[1], COL_G);
}

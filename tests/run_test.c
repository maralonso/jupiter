#include "test_generation.h"
#include "test_pieces.h"
#include "test_rook.h"
#include "test_bishop.h"
#include "test_knight.h"
#include "test_king.h"
#include "test_pawn.h"
#include "cu/cu.h"

TEST_SUITES {
      TEST_SUITE_ADD(generation), 
      TEST_SUITE_ADD(pieces), 
      TEST_SUITE_ADD(rook_moves), 
      TEST_SUITE_ADD(bishop_moves), 
      TEST_SUITE_ADD(knight_moves), 
      TEST_SUITE_ADD(king_moves), 
      TEST_SUITE_ADD(pawn_moves),
      TEST_SUITES_CLOSURE
};

int main(int argc, char *argv[])
{
   CU_RUN(argc, argv);
   return 0;
}

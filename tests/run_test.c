#include "test_generation.h"
#include "test_pieces.h"
#include "test_rook.h"
#include "test_bishop.h"
#include "test_knight.h"
#include "test_king.h"
#include "test_pawn.h"
#include "test_node.h"
#include "test_fen.h"
#include "test_evaluation.h"
#include "test_notation.h"
#include "test_uci.h"
#include "cu/cu.h"

TEST_SUITES {
      TEST_SUITE_ADD(node), 
      TEST_SUITE_ADD(generation), 
      TEST_SUITE_ADD(pieces), 
      TEST_SUITE_ADD(rook_moves), 
      TEST_SUITE_ADD(bishop_moves), 
      TEST_SUITE_ADD(knight_moves), 
      TEST_SUITE_ADD(king_moves), 
      TEST_SUITE_ADD(pawn_moves),
      TEST_SUITE_ADD(fen_utils),
      TEST_SUITE_ADD(evaluation),
      TEST_SUITE_ADD(notation),
      TEST_SUITE_ADD(test_uci),
      TEST_SUITES_CLOSURE
};

int main(int argc, char *argv[])
{
   CU_RUN(argc, argv);
   return 0;
}

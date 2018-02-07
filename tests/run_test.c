#include "test_generation.h"
#include "test_pieces.h"
#include "test_rook.h"
#include "cu/cu.h"

TEST_SUITES {
      TEST_SUITE_ADD(generation), 
      TEST_SUITE_ADD(rook_moves), 
      TEST_SUITE_ADD(pieces), 
      TEST_SUITES_CLOSURE
};

int main(int argc, char *argv[])
{
   CU_RUN(argc, argv);
   return 0;
}

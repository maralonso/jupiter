#include "board.h"
#include "CuTest.h"
#include "generation.h"


void TestBoardinit(CuTest* tc)
{
    Node_t node;
    retval_t rv;

    rv = node_init(&node);

    CuAssertIntEquals(tc, rv, RV_SUCCESS);
}


CuSuite* getGenerationSuite(void)
{
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, TestBoardinit);

    return suite;
}

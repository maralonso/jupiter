#include "cu/cu.h"

TEST(test_insert_node);
TEST(test_delete_node);

TEST_SUITE(node) {
    TEST_ADD(test_insert_node),
    TEST_ADD(test_delete_node),
    TEST_SUITE_CLOSURE
};



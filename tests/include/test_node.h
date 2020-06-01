#include "cu/cu.h"

TEST(test_insert_node);
TEST(test_delete_node);
TEST(test_get_deep_count);

TEST_SUITE(node) {
    TEST_ADD(test_insert_node),
    TEST_ADD(test_delete_node),
    TEST_ADD(test_get_deep_count),
    TEST_SUITE_CLOSURE
};

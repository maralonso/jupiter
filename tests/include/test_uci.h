#include "cu/cu.h"

TEST(decode_cmd_quit);
TEST(decode_cmd_debug);
TEST(decode_cmd_isready);
TEST(decode_cmd_setoption);
TEST(decode_cmd_register);
TEST(decode_cmd_newgame);
TEST(decode_cmd_position);
TEST(decode_cmd_go);
TEST(decode_cmd_stop);
TEST(decode_cmd_stop);
TEST(cmd_is_ready);


TEST_SUITE(test_uci) {
    TEST_ADD(decode_cmd_quit),
    TEST_ADD(decode_cmd_debug),
    TEST_ADD(decode_cmd_isready),
    TEST_ADD(decode_cmd_setoption),
    TEST_ADD(decode_cmd_register),
    TEST_ADD(decode_cmd_position),
    TEST_ADD(decode_cmd_newgame),
    TEST_ADD(decode_cmd_go),
    TEST_ADD(decode_cmd_stop),
    TEST_ADD(decode_cmd_stop),
    TEST_ADD(decode_cmd_stop),
    TEST_ADD(cmd_is_ready),
    TEST_SUITE_CLOSURE
};


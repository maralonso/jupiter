#include "board.h"
#include "cu/cu.h"
#include "stdio.h"
#include "node.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "uci.h"
#include "fen.h"

typedef enum {
    INVALID_CMD = 0,
    UCI,
    DEBUG,
    ISREADY,
    SETOPT,
    REGISTER,
    NEWGAME,
    POSITION,
    GO,
    STOP,
    PONDERHIT,
    QUIT,
} command_code_t;

typedef struct {
    char key[20];
    union {
        int i;
        bool b;
        char s[20];
    } value;
} option_t;

typedef struct {
    char fen[MAX_FEN_LEN];
    char moves[MAX_FEN_LEN];
} position_t;

typedef enum {
    INFINITE,
    TIME,
    DEPTH,
} go_modes_t;

typedef struct {
    go_modes_t mode;
    uint8_t depth;
    bool ponder;
    char *searchmoves[10];
    uint32_t wtime;
    uint32_t btime;
    uint32_t winc;
    uint32_t binc;
} go_t; 
 
typedef struct {
    command_code_t code;
    union {
        option_t option;
        position_t pos;
        go_t go;
    } body;
}command_t;
 
extern command_t decode_command(char *str);

TEST(decode_cmd_quit)
{
    command_t cmd;
    char cmd_str[] = "quit\n";

    cmd = decode_command(cmd_str);
    assertEquals(cmd.code, QUIT);
}

TEST(decode_cmd_debug)
{
    command_t cmd;
    char cmd_str[] = "debug\n";

    cmd = decode_command(cmd_str);
    assertEquals(cmd.code, DEBUG);
}

TEST(decode_cmd_isready)
{
    command_t cmd;
    char cmd_str[] = "isready\n";

    cmd = decode_command(cmd_str);
    assertEquals(cmd.code, ISREADY);
}

TEST(decode_cmd_setoption)
{
    command_t cmd;
    char cmd_str[] = "setoption\n";

    cmd = decode_command(cmd_str);
    assertEquals(cmd.code, SETOPT);
}

TEST(decode_cmd_register)
{
    command_t cmd;
    char cmd_str[] = "register\n";

    cmd = decode_command(cmd_str);
    assertEquals(cmd.code, REGISTER);
}

TEST(decode_cmd_newgame)
{
    command_t cmd;
    char cmd_str[] = "ucinewgame\n";

    cmd = decode_command(cmd_str);
    assertEquals(cmd.code, NEWGAME);
}

TEST(decode_cmd_position)
{
    command_t cmd;
    char cmd_str[] = "position startpos moves e2e4\n";

    cmd = decode_command(cmd_str);

    assertEquals(cmd.code, POSITION);
    assertEquals(0, strncmp(cmd.body.pos.fen, "startpos", strlen("startpos")));
    assertEquals(0, strncmp(cmd.body.pos.moves, "e2e4", strlen("e2e4")));
  
    char cmd_str2[] = "position fen 8/8/8/k7/8/8/8/K7 w - 10 30 moves e2e4\n";
    cmd = decode_command(cmd_str2);

    assertEquals(cmd.code, POSITION);
    assertEquals(0, strncmp(cmd.body.pos.fen, "8/8/8/k7/8/8/8/K7 w - 10 30",
                 strlen("8/8/8/k7/8/8/8/K7 w - 10 30")));
    assertEquals(0, strncmp(cmd.body.pos.moves, "e2e4", strlen("e2e4")));
}

TEST(decode_cmd_go)
{
    command_t cmd;
    char cmd_str[] = "go infinite\n";

    cmd = decode_command(cmd_str);
    assertEquals(cmd.code, GO);
    assertEquals(cmd.body.go.mode, INFINITE);

    char cmd_str2[] = "go depth 5\n";
    cmd = decode_command(cmd_str2);
    assertEquals(cmd.code, GO);
    assertEquals(cmd.body.go.mode, DEPTH);
    assertEquals(cmd.body.go.depth, 5);
    
    char cmd_str3[] = "go wtime 20000 winc 0 btime 1000 binc 0\n";
    cmd = decode_command(cmd_str3);
    assertEquals(cmd.code, GO);
    assertEquals(cmd.body.go.mode, TIME);
    assertEquals(cmd.body.go.wtime, 20000);
    assertEquals(cmd.body.go.btime, 1000);
    assertEquals(cmd.body.go.winc, 0);
    assertEquals(cmd.body.go.binc, 0);
}

TEST(decode_cmd_stop)
{
    command_t cmd;
    char cmd_str[] = "stop\n";

    cmd = decode_command(cmd_str);
    assertEquals(cmd.code, STOP);
}

TEST(decode_cmd_ponderhit)
{
    command_t cmd;
    char cmd_str[] = "ponderhit\n";

    cmd = decode_command(cmd_str);
    assertEquals(cmd.code, PONDERHIT);
}

TEST(decode_cmd_uci)
{
    command_t cmd;
    char cmd_str[] = "uci\n";

    cmd = decode_command(cmd_str);
    assertEquals(cmd.code, UCI);
}


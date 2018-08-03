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
 
extern void decode_command(char *str, command_t *cmd);

TEST(decode_cmd_quit)
{
    command_t cmd;
    char cmd_str[] = "quit\n";

    decode_command(cmd_str, &cmd);
    assertEquals(cmd.code, QUIT);
}

TEST(decode_cmd_debug)
{
    command_t cmd;
    char cmd_str[] = "debug\n";

    decode_command(cmd_str, &cmd);
    assertEquals(cmd.code, DEBUG);
}

TEST(decode_cmd_isready)
{
    command_t cmd;
    char cmd_str[] = "isready\n";

    decode_command(cmd_str, &cmd);
    assertEquals(cmd.code, ISREADY);
}

TEST(decode_cmd_setoption)
{
    command_t cmd;
    char cmd_str[] = "setoption\n";

    decode_command(cmd_str, &cmd);
    assertEquals(cmd.code, SETOPT);
}

TEST(decode_cmd_register)
{
    command_t cmd;
    char cmd_str[] = "register\n";

    decode_command(cmd_str, &cmd);
    assertEquals(cmd.code, REGISTER);
}

TEST(decode_cmd_newgame)
{
    command_t cmd;
    char cmd_str[] = "ucinewgame\n";

    decode_command(cmd_str, &cmd);
    assertEquals(cmd.code, NEWGAME);
}

TEST(decode_cmd_position)
{
    command_t cmd;
    char cmd_str[] = "position startpos moves e2e4\n";

    decode_command(cmd_str, &cmd);

    assertEquals(cmd.code, POSITION);
    assertEquals(0, strncmp(cmd.body.pos.fen, "startpos", strlen("startpos")));
    assertEquals(0, strncmp(cmd.body.pos.moves, "e2e4", strlen("e2e4")));
  
    char cmd_str2[] = "position fen 8/8/8/k7/8/8/8/K7 w - 10 30 moves e2e4\n";
    decode_command(cmd_str2, &cmd);

    assertEquals(cmd.code, POSITION);
    assertEquals(0, strncmp(cmd.body.pos.fen, "8/8/8/k7/8/8/8/K7 w - 10 30",
                 strlen("8/8/8/k7/8/8/8/K7 w - 10 30")));
    assertEquals(0, strncmp(cmd.body.pos.moves, "e2e4", strlen("e2e4")));
}

TEST(decode_cmd_go)
{
    command_t cmd;
    char cmd_str[] = "go infinite\n";

    decode_command(cmd_str, &cmd);
    assertEquals(cmd.code, GO);
    assertEquals(cmd.body.go.mode, INFINITE);

    char cmd_str2[] = "go depth 5\n";
    decode_command(cmd_str2, &cmd);
    assertEquals(cmd.code, GO);
    assertEquals(cmd.body.go.mode, DEPTH);
    assertEquals(cmd.body.go.depth, 5);
    
    char cmd_str3[] = "go wtime 20000 winc 0 btime 1000 binc 0\n";
    decode_command(cmd_str3, &cmd);
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

    decode_command(cmd_str, &cmd);
    assertEquals(cmd.code, STOP);
}

TEST(decode_cmd_ponderhit)
{
    command_t cmd;
    char cmd_str[] = "ponderhit\n";

    decode_command(cmd_str, &cmd);
    assertEquals(cmd.code, PONDERHIT);
}

TEST(decode_cmd_uci)
{
    command_t cmd;
    char cmd_str[] = "uci\n";

    decode_command(cmd_str, &cmd);
    assertEquals(cmd.code, UCI);
}

TEST(cmd_is_ready)
{
    int old_stdout = dup(1);
    FILE *in = fopen("tests/tmp_stdin.txt", "wb");
    char response[100];

    fprintf(in, "%s\n", "isready");
    fprintf(in, "%s\n", "quit");
    fclose(in);

    freopen("tests/tmp_stdin.txt", "r", stdin);
    freopen("tests/tmp_stdout.txt", "wb", stdout);

    uci_main();

    FILE *out = fopen("tests/tmp_stdout.txt", "r");
    while (!feof(out)) {
        fgets(response, 100, out);
    }
    assertEquals(0, strncmp(response, "readyok", strlen("readyok")));

    dup2(old_stdout, 1);
}

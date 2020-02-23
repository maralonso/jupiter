#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <poll.h>
#include <pthread.h>

#include "generation.h"
#include "fen.h"
#include "notation.h"
#include "engine.h"
#include "logging.h"
#include "node.h"

//GUI to engine
#define CMD_UCI         "uci"
#define CMD_DEBUG       "debug"
#define CMD_IS_RDY      "isready"
#define CMD_SET_OPT     "setopt"
#define CMD_REGISTER    "register"
#define CMD_NEW_GAME    "ucinewgame"
#define CMD_POSITION    "position"
#define CMD_GO          "go"
#define CMD_STOP        "stop"
#define CMD_PONDERHIT   "ponderhit"
#define CMD_QUIT        "quit"

//engine to GUI
#define CMD_ID_NAME     "id name Jupiter"
#define CMD_ID_AUTHOR   "id author Martin Alonso"
#define CMD_UCI_OK      "uciok"
#define CMD_RDY_OK      "readyok"
#define CMD_BEST_MOVE   "bestmove"
#define CMD_CPY_PROT    "copypretection"
#define CMD_REGIST      "registration"
#define CMD_INFO        "info"
#define CMD_OPTION      "option"

#define MAX_CMD_STR_LEN 1000
#define MAX_MOVES_SRT_LEN (2 * 5 * 120)
static Node_t *node;

typedef enum {
    INVALID_CMD = 0,
    UCI,
    DBG,
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
    char moves[MAX_MOVES_SRT_LEN];
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

#define CMD_BUFFER_SIZE 5
typedef struct {
    command_t cmd[CMD_BUFFER_SIZE];
    pthread_mutex_t mutex;
    pthread_cond_t cond_prod;
    pthread_cond_t cond_consum;
    size_t len;
}command_buffer_t;

static void send_command(const char *cmd)
{
    int fd = dup(STDOUT_FILENO);
    write(fd, cmd, strlen(cmd));
    write(fd, "\n", 1);
    LOG2(INFO, "engine:", cmd);
}

static void receive_command(char *cmd)
{
    fgets(cmd, MAX_CMD_STR_LEN, stdin);
    cmd[strlen(cmd) - 1] = 0x0;
    LOG2(INFO, "gui:", cmd);
}

static retval_t decode_position(command_t *cmd, char *str)
{
    char *token = strtok(NULL, " ");
    memset(cmd->body.pos.fen, 0x0, MAX_FEN_LEN);
    memset(cmd->body.pos.moves, 0x0, MAX_FEN_LEN);
       
    if (strncmp(token, "startpos", strlen("startpos")) == 0) {
        strncpy(cmd->body.pos.fen, "startpos", strlen("startpos") + 1);
        token = strtok(NULL, " ");
    } else if (strncmp(token, "fen", strlen("fen")) == 0) {
        token = strtok(NULL, " ");
        while (token != NULL &&  strncmp(token, "moves", strlen("moves")) != 0) {
            strcat(cmd->body.pos.fen, token);
            strcat(cmd->body.pos.fen, " ");
            token = strtok(NULL, " ");
        }
    } else {
        return RV_ERROR;
    }

    if (token != NULL && strncmp(token, "moves", strlen("moves")) == 0) {
        token = strtok(NULL, " ");
        while (token != NULL) {
            strcat(cmd->body.pos.moves, token);
            strcat(cmd->body.pos.moves, " ");
            token = strtok(NULL, " ");
        }
    }
    return RV_SUCCESS;
}

static retval_t decode_go(command_t *cmd, char *str)
{
    cmd->body.go.mode = TIME;
    cmd->body.go.ponder = false;
    cmd->body.go.depth = 0;
    cmd->body.go.wtime = 0;
    cmd->body.go.btime = 0;
    cmd->body.go.winc = 0;
    cmd->body.go.binc = 0;

    char *token = strtok(NULL, " ");
    while (token != NULL) {   
        if (strncmp(token, "infinite", strlen("infinite")) == 0) {
            cmd->body.go.mode = INFINITE;
        }
        if (strncmp(token, "ponder", strlen("ponder")) == 0) {
            cmd->body.go.ponder = true;
        }
        if (strncmp(token, "depth", strlen("depth")) == 0) {
            token = strtok(NULL, " ");
            cmd->body.go.mode = DEPTH;
            cmd->body.go.depth = atoi(token);
        }
        if (strncmp(token, "wtime", strlen("wtime")) == 0) {
            token = strtok(NULL, " ");
            cmd->body.go.wtime = atoi(token);
        }
        if (strncmp(token, "btime", strlen("btime")) == 0) {
            token = strtok(NULL, " ");
            cmd->body.go.btime = atoi(token);
        }
        if (strncmp(token, "binc", strlen("binc")) == 0) {
            token = strtok(NULL, " ");
            cmd->body.go.binc = atoi(token);
        }
        if (strncmp(token, "winc", strlen("winc")) == 0) {
            token = strtok(NULL, " ");
            cmd->body.go.winc = atoi(token);
        }
        token = strtok(NULL, " ");
    }

    return RV_SUCCESS;
}

void decode_command(char *cmd_str, command_t *cmd)
{
    retval_t rv;
    cmd->code = INVALID_CMD;
    char *token = strtok(cmd_str, " ");

    while (token) {
        if (strncmp(cmd_str, CMD_QUIT, strlen(CMD_QUIT)) == 0) {
            cmd->code = QUIT;
            break;
        } else if (strncmp(cmd_str, CMD_DEBUG, strlen(CMD_DEBUG)) == 0) {
            cmd->code = DBG;
            break;
        } else if (strncmp(cmd_str, CMD_IS_RDY, strlen(CMD_IS_RDY)) == 0) {
            cmd->code = ISREADY;
            break;
        } else if (strncmp(cmd_str, CMD_SET_OPT, strlen(CMD_SET_OPT)) == 0) {
            cmd->code = SETOPT;
            //TODO
            //decode_options
            break;
        } else if (strncmp(cmd_str, CMD_REGISTER, strlen(CMD_REGISTER)) == 0) {
            cmd->code = REGISTER;
            break;
        } else if (strncmp(cmd_str, CMD_NEW_GAME, strlen(CMD_NEW_GAME)) == 0) {
            cmd->code = NEWGAME;
            break;
        } else if (strncmp(cmd_str, CMD_POSITION, strlen(CMD_POSITION)) == 0) {
            rv = decode_position(cmd, cmd_str);
            if (rv == RV_SUCCESS) {
                cmd->code = POSITION;
            }
            break;
        } else if (strncmp(cmd_str, CMD_GO, strlen(CMD_GO)) == 0) {
            cmd->code = GO;
            decode_go(cmd, cmd_str);
            break;
        } else if (strncmp(cmd_str, CMD_STOP, strlen(CMD_STOP)) == 0) {
            cmd->code = STOP;
            break;
        } else if (strncmp(cmd_str, CMD_PONDERHIT, strlen(CMD_PONDERHIT)) == 0) {
            cmd->code = PONDERHIT;
            break;
        } else if (strncmp(cmd_str, CMD_UCI, strlen(CMD_UCI)) == 0) {
            cmd->code = UCI;
            break;
        }

        token = strtok(NULL, " ");
    }
}

static void uci_is_ready()
{
    send_command(CMD_RDY_OK);
}

static void uci_position(command_t *cmd)
{
    if (strncmp(cmd->body.pos.fen, "startpos", strlen("startpos")) == 0) {
        move_init(&node);
    } else {
        node = create_node();
        get_node_from_fen(node, cmd->body.pos.fen);
    }
    
    char *token = strtok(cmd->body.pos.moves, " ");
    while (token != NULL) {
        Move_t mov;
        if (RV_SUCCESS == get_move_from_notation(&mov, token)) {
            make_move(node, mov);
        }
        token = strtok(NULL, " ");
    }
}

static void uci_go(command_t *cmd)
{
    char *mov;
    char cmd_mov[NOTATION_STR_LEN + 10];
    engine_cfg_t cfg;
    
    if (cmd->body.go.mode == INFINITE) {
        cfg.mode = ENGINE_INFINITE;
    }
    if (cmd->body.go.mode == DEPTH) {
        cfg.mode = ENGINE_DEPTH;
        cfg.data.depth = cmd->body.go.depth;
    }
    if (cmd->body.go.mode == TIME) {
        cfg.mode = ENGINE_TIME;
        cfg.data.time = node->turn == WHITE? cmd->body.go.wtime: cmd->body.go.btime;
    }
        
        
    engine_set_log_func(send_command);
    mov = engine_go(node, cfg);
    sprintf(cmd_mov, "%s %s", "bestmove", mov);
    send_command(cmd_mov);
}

static void uci_init()
{
    send_command(CMD_ID_NAME);
    send_command(CMD_ID_AUTHOR);
    send_command(CMD_UCI_OK);
}

static void buffer_pop(command_buffer_t *buffer, command_t *cmd)
{
    pthread_mutex_lock(&buffer->mutex);

    if(buffer->len == 0) { 
        pthread_cond_wait(&buffer->cond_consum, &buffer->mutex);
    }

    --buffer->len;
    memcpy(cmd, &(buffer->cmd[buffer->len]), sizeof(command_t));

    pthread_cond_signal(&buffer->cond_prod);
    pthread_mutex_unlock(&buffer->mutex);
}

static void buffer_push(command_buffer_t *buffer, command_t *cmd)
{
    pthread_mutex_lock(&buffer->mutex);

    if(buffer->len == CMD_BUFFER_SIZE) { 
        pthread_cond_wait(&buffer->cond_prod, &buffer->mutex);
    }

    memcpy(&(buffer->cmd[buffer->len]), cmd, sizeof(command_t));
    ++buffer->len;

    pthread_cond_signal(&buffer->cond_consum);
    pthread_mutex_unlock(&buffer->mutex);
}

static void *command_receiver(void *buffer)
{
    command_buffer_t *buff = (command_buffer_t *) buffer;
    static char cmd_str[MAX_CMD_STR_LEN];
    static command_t cmd;
    
    while(true) {
        receive_command(cmd_str);
        decode_command(cmd_str, &cmd);

        switch (cmd.code) {
            case DBG:
            case SETOPT:
            case REGISTER:
            case NEWGAME:
            case PONDERHIT:
            case INVALID_CMD:
                break;   
            case STOP:
                engine_stop();
                break;
            case GO:
                buffer_push(buff, &cmd);
                break;
            case POSITION:
                uci_position(&cmd);
                break;
            case ISREADY:
                uci_is_ready();
                break;
            case UCI:
                uci_init();
                break;
            case QUIT:
                buffer_push(buff, &cmd);
                return NULL;
        }
    }
    return NULL;
}

static void *command_executor(void *buffer)
{
    command_buffer_t *buff = (command_buffer_t *) buffer;
    static command_t cmd;

    while (true) {
        buffer_pop(buff, &cmd);
        if (cmd.code == GO) {
            uci_go(&cmd);
        }
        if (cmd.code == QUIT) {
            break;
        }
    } 

    return NULL;
}

void uci_main()
{
    pthread_t receiver;
    pthread_t executor;

    command_buffer_t buffer = {
        .mutex = PTHREAD_MUTEX_INITIALIZER,
        .cond_prod = PTHREAD_COND_INITIALIZER,
        .cond_consum = PTHREAD_COND_INITIALIZER,
        .len = 0,
    };

    uci_init();

    if (pthread_create(&receiver, NULL, &command_receiver, &buffer)) {
        printf("Could not create pthread\n");
        exit(1);
    }

    if (pthread_create(&executor, NULL, &command_executor, &buffer)) {
        printf("Could not create pthread\n");
        exit(1);
    }
    
    pthread_join(receiver, NULL);
    pthread_join(executor, NULL);
}

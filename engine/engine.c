#include <stdio.h>
#include <omp.h>

#include "board.h"
#include "generation.h"
#include "evaluation.h"
#include "notation.h"
#include "engine.h"
#include "node.h"
#include "delay.h"
#include "search.h"
#include "fen.h"
#include "logging.h"

static bool engine_keep_running = true;

static void (*log_func)(const char *info) = NULL;

typedef struct {
    char mov[NOTATION_STR_LEN];
    uint32_t nodes_count;
    uint32_t score;
    uint32_t nps;
    double time;
} engine_info_t;

static engine_info_t engine_think(Node_t *node)
{
    engine_info_t info;
    double start, end;
    uint64_t perft_nodes;

    start = omp_get_wtime();

    generate(node);
    get_best_move(node, info.mov);

    end = omp_get_wtime();
    info.time = end - start;
    info.nodes_count = get_tree_count(node) - 1;
    perft_nodes = perft(node);
    if (info.time > 0) {
        info.nps = (perft_nodes * 1000) / info.time;
    } else {
        info.nps = 0;
    }

    return info;
}

static bool keep_running(engine_cfg_t cfg, uint32_t elapsed_time, uint8_t current_depth)
{
    if (!engine_keep_running) {
        return false;
    }
    if (cfg.mode == ENGINE_TIME) {
        if ((cfg.data.time / 5000) < elapsed_time) {
            return false;
        }
    }
    if (cfg.mode == ENGINE_DEPTH) {
        if (current_depth >= cfg.data.depth) {
            return false;
        }
    }
        
    return true;        
}

static void log_info(engine_info_t info, uint8_t depth, double elapsed_time)
{
    char msg[1000];

    if (log_func != NULL) {
        sprintf(msg, "info depth %d score cp %d time %f nodes %d nps %d",
              depth, info.score, elapsed_time, info.nodes_count,
              info.nps);
        log_func(msg);
    }
}

void engine_set_log_func(void *func)
{
    log_func = func;
}

char* engine_go(Node_t *node, engine_cfg_t cfg)
{
    static engine_info_t info;
    double elapsed_time = 0.0f;
    uint8_t current_depth = 0;

    char fen[MAX_FEN_LEN];
    get_fen_from_node(node, fen);
    LOG2(DEBUG, "Board: ", fen);
    engine_keep_running = true;

    while (keep_running(cfg, elapsed_time, current_depth)) {
        info = engine_think(node);
        current_depth++;
        elapsed_time += info.time;
        log_info(info, current_depth, elapsed_time);
    } 

    delete_node(node);
    return info.mov;
} 

void engine_stop(void)
{
    engine_keep_running = false;
}

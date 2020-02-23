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

static int get_node_childs(Node_t *node)
{
    Node_t *aux;
    int count = 0;
    if (node->child != NULL) {
        aux = node->child;
        while (aux != NULL) {
            count++;
            aux = aux->next;
        }
    }

    return count;
}

static void generate_nodes(Node_t *node)
{
    Node_t *aux = node;

    while(aux != NULL) {
        if (aux->child != NULL) {
            generate_nodes(aux->child);
        } else { 
            get_moves(aux);
        }
        aux = aux->next;
    }
}

static void parallel_generation(Node_t *node)
{
    int node_childs = get_node_childs(node);

    if (node_childs == 0) {
        generate_nodes(node);
    } else {
        #pragma  omp parallel
        {
            #pragma omp for schedule(guided, 5)
            for (int i=0; i < node_childs; i++) {
                Node_t *child = node->child;
                for (int j=0; j < i; j++) {
                        child = child->next;
                }
                if (child->child != NULL) {
                    generate_nodes(child->child);
                } else {
                    get_moves(child);
                }
            }
        }
    }
}

static engine_info_t engine_think(Node_t *node)
{
    engine_info_t info;
    double start, end;
    
    start = omp_get_wtime();

    parallel_generation(node);
    get_best_move(node, info.mov);

    end = omp_get_wtime();
    info.time = end - start;
    info.nodes_count = get_tree_count(node) - 1;
    if (info.time > 0) {
        info.nps = (info.nodes_count * 1000) / info.time;
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

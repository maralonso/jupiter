#ifndef _ENGINE_H_
#define _ENGINE_H_

typedef enum {
    ENGINE_INFINITE,
    ENGINE_TIME,
    ENGINE_DEPTH,
} engine_mode_t;

typedef struct {
    engine_mode_t mode;
    union {
        uint8_t depth;
        uint32_t time;
    }data;
} engine_cfg_t;

void engine_set_log_func(void *func);
char* engine_go(Node_t *node, engine_cfg_t cfg);

#endif

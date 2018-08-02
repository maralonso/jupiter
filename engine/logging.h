#ifndef __LOGGING_H__
#define __LOGGING_H__

#include "board.h"

typedef enum {
    DEBUG = 0,
    INFO,
    ERROR,
} log_priority_t;

#define MAX_PRIORITY_LEN 8
static const char priorities[][MAX_PRIORITY_LEN] = {
    "[DEBUG]",
    "[INFO]",
    "[ERROR]"
};


retval_t logging_init();
void logging(log_priority_t log_level, const char *msg, const char *msg2);
log_priority_t get_priority_from_string(char *str);

#define LOG(lev, msg)   (logging(lev, msg, ""))
#define LOG2(lev, msg, msg2)   (logging(lev, msg, msg2))

#define DEFAULT_LOG_DIR "/tmp/jupiter"
#define DEFAULT_LOG_FILE "/tmp/jupiter/jupiter.log"
#endif

#ifndef __CONFIG_H_
#define __CONFIG_H_

#include "logging.h"

#define MAX_LOG_FILE_LEN    30

#define KEY_LOG_LEVEL   "LOG_LEVEL"
#define KEY_LOG_FILE    "LOG_FILE"


typedef struct {
   log_priority_t log_level;

   char log_file[MAX_LOG_FILE_LEN] ;
} config_t;


config_t config;

void get_conf();

#endif

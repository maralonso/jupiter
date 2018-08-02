#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "logging.h"
#include "config.h"

static bool initialized = false;

#define MAX_TIME_STR_LEN    80

static void get_time_str(char *buffer)
{
    time_t rawtime;
    struct tm *info;

    time( &rawtime );
    info = localtime( &rawtime );
    strftime(buffer, MAX_TIME_STR_LEN,"%x - %I:%M%p", info);
}

log_priority_t get_priority_from_string(char *str)
{
    if (strncmp(str, priorities[DEBUG], strlen(priorities[DEBUG]))) {
        return DEBUG;
    } 
    if (strncmp(str, priorities[INFO], strlen(priorities[INFO]))) {
        return INFO;
    }
    if (strncmp(str, priorities[ERROR], strlen(priorities[ERROR]))) {
        return ERROR;
    }

    /* Should not reach here.
     * returns defaulr value */
    return INFO;
}

retval_t logging_init()
{
    struct stat st = {0};
    
    if (stat(DEFAULT_LOG_DIR, &st) == -1) {
        mkdir(DEFAULT_LOG_DIR, 0700);
    }
    
    FILE *f = fopen(config.log_file, "w");
    if (f != NULL) {
        initialized = true;
        fclose(f);
        printf("Using logging file: %s\n", config.log_file);
    } else {
        strcpy(config.log_file, DEFAULT_LOG_FILE);
        f = fopen(config.log_file, "w");
        if (f != NULL) {
            printf("Could not open logging file %s\n", config.log_file);
            printf("Using default file: %s\n", DEFAULT_LOG_FILE);
            initialized = true;
            fclose(f);
        }
    }
    printf("Logging level set to %s\n", priorities[config.log_level]);
    return RV_SUCCESS;
}

void logging(log_priority_t log_level, const char *msg, const char *msg2)
{
    if (!initialized) {
        return;
    }

    if (log_level < config.log_level) {
        return;
    }

    char time_str[MAX_TIME_STR_LEN];
    get_time_str(time_str);
    
    FILE *f = fopen(config.log_file, "a+");
    if (f) {
        fprintf(f, "[%s] - %s\t%s %s\n", time_str, priorities[log_level], msg, msg2);
        fclose(f);
    }
}

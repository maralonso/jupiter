#include <stdio.h>
#include <string.h>
#include "config.h"

#define MAX_LINE_LEN 80
#define CONFIG_FILE "engine/config"

static void parse_line(char *line)
{
    if (strstr(line, KEY_LOG_LEVEL)){
            char *value = strchr(line, '=');
            if (value) {
                config.log_level = get_priority_from_string(&value[1]);
            }
    }
    if (strstr(line, KEY_LOG_FILE)){
            char *value = strchr(line, '=');
                
            if (value) {
                value[strlen(value) - 1] = 0x0;
                int i = 0;
                while (value[++i] == ' ');
                strcpy(config.log_file, &value[i]);
            }
    }
}

void get_conf()
{
    char buffer[MAX_LINE_LEN]; 
    FILE *cfg = fopen(CONFIG_FILE, "r");

    if (cfg == NULL) {
        return;
    }

    while (fgets(buffer, MAX_LINE_LEN, cfg)) {
        if (strlen(buffer) > 1 && buffer[0] != '#') { 
            parse_line(buffer);
        }
    }

    fclose(cfg);
}

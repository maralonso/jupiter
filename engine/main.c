#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "delay.h"
#include <poll.h>
#include "uci.h"
#include "config.h"

#define WAIT_FOR_GUI_MS -1

#define MAX_USER_MODE_STR_LEN   20
#define UCI_STR "uci"

typedef enum {
    UCI_MODE,
    CONSOLE_MODE,
    XBOARD_MODE,
    UNDEF_MODE, 
} user_mode_t;

user_mode_t get_user_mode()
{
    user_mode_t mode = UNDEF_MODE;
    struct pollfd mpoll = {STDIN_FILENO, POLLIN};
    char str_mode[MAX_USER_MODE_STR_LEN];

    if (poll(&mpoll, 1, WAIT_FOR_GUI_MS)) {
        fgets(str_mode, 100, stdin);
        str_mode[strlen(str_mode) - 1] = 0x0;
        if (strncmp(str_mode, UCI_STR, strlen(UCI_STR)) == 0) {
            mode = UCI_MODE;
        }
    } else {
        puts("No GUI detected...");
    }

    return mode;
}

static void print_logo()
{
    FILE *f = fopen("ascii.txt", "r");
    if (f) {
        while (!feof(f)) {
            char line[80];
            memset(line, 0x0, 80);
            fgets(line, 80, f);
            printf(line);
        }
     fclose(f);   
    }
}

static void init()
{
    print_logo();
    config.log_level = INFO;
    strcpy(config.log_file, DEFAULT_LOG_FILE);

    get_conf();
    logging_init();
}

int main(void)
{
    init();

    switch (get_user_mode()) {
        case UCI_MODE:
            uci_main();
            break;
        case XBOARD_MODE:
        case CONSOLE_MODE:
        case UNDEF_MODE:
            puts("Not implemented mode... yet");
            break;
    }

    return 0;
}

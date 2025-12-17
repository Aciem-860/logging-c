#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"
#define CRESET "\e[0m"

typedef enum {
    NONE,
    INFO,
    DEBUG,
    WARNING,
    ERROR,
    ALL
} LogLevel;

void init_logg(FILE* file, int rc, LogLevel max_lvl);
void logg(LogLevel level, char *msg, ...);

#ifdef LOG_IMPL
#include <assert.h>

static FILE *file;
static int render_colours = 0;
static LogLevel max_level = ERROR;

void init_logg(FILE *f, int rc, LogLevel max_lvl) {
    file = f;
    render_colours = rc;
    max_level = max_lvl;
}

void logg(LogLevel level, char* msg, ...) {
    assert(file != NULL);

    if (level > max_level) return;
    
    char* colour;
    char* colour_reset;
    char* prefix;

    switch(level) {
    case INFO:
        colour = BLU;
        prefix = "INFO";
        break;
    case DEBUG:
        colour = GRN;
        prefix = "DEBUG";
        break;
    case WARNING:
        colour = YEL;
        prefix = "WARNING";
        break;
    case ERROR:
        colour = RED;
        prefix = "ERROR";
        break;
    case NONE:
    case ALL:
        fprintf(stderr, "You should not use NONE or ALL when calling logg function!\n");
        exit(1);
    }

    if (!render_colours) {
        colour = "";
        colour_reset = "";
    } else {
        colour_reset = CRESET;
    }

    char msg_buf[64];

    va_list args;
    va_start(args, msg);
    vsprintf(msg_buf, msg, args);
    fprintf(file, "%s[ %7s ]%s %s\n", colour, prefix, colour_reset, msg_buf);
    va_end(args);
}

#endif
#endif

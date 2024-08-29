/**
 * @file trace.c
 * @author your name (chucktilbury@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-08-19
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define INDENT 4
static int indent = 0;

static void pad(void) {

    for(int i = 0; i < indent; i++)
        fputc(' ', stdout);
}

void trace_enter(const char* func) {

    pad();
    printf("ENTER: %s\n", func);
    indent += INDENT;
}

void trace_return(const char* func, size_t val) {

    indent -= INDENT;
    pad();
    printf("RETURN: %s: 0x%08lX\n", func, val);
}

void trace(const char* func, const char* fmt, ...) {

    va_list args;

    pad();
    printf("TRACE: %s: ", func);
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    fputc('\n', stdout);
}

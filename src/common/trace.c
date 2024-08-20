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

#define INDENT 2
static int indent = 0;

void trace_enter(const char* func) {

    printf("%*cENTER: %s\n", indent, ' ', func);
    indent += INDENT;
}

void trace_return(const char* func, size_t val) {

    indent += INDENT;
    printf("%*cRETURN: %s: 0x%016lX\n", indent, ' ', func, val);
}

void trace_state(const char* func, int state) {

    printf("%*cSTATE: %s: %d\n", indent, ' ', func, state);
}

void trace(const char* func, const char* fmt, ...) {

    va_list args;

    printf("%*cTRACE: %s: ", indent, ' ', func);
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    fputc('\n', stdout);
}

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

#include "llist.h"
#include "trace.h"
#include "myassert.h"
#include "memory.h"

static LinkList* stack = NULL;

static inline void pad(void) {

    for(int i = 0; i < indent; i++)
        fputc(' ', stdout);
}

void init_trace(void) {

    if(stack == NULL) {
        stack = create_link_list();
        TraceState state = TRACE_OFF;
        push_link_list(stack, _DUP_DS(&state, TraceState));
    }
    // else do nothing
}

void trace_enter(const char* func) {

    ASSERT_MSG(stack != NULL, "trace is not initialized");

    TraceState* s = peek_link_list(stack);
    if(*s != 0) {
        pad();
        printf("ENTER: %s\n", func);
        indent += INDENT;
    }
}

void trace_return(const char* func, size_t val) {

    ASSERT_MSG(stack != NULL, "trace is not initialized");

    TraceState* s = peek_link_list(stack);
    if(*s != 0) {
        indent -= INDENT;
        pad();
        printf("RETURN: %s: 0x%08lX\n", func, val);
    }
}

void trace_return_noval(const char* func) {

    ASSERT_MSG(stack != NULL, "trace is not initialized");

    TraceState* s = peek_link_list(stack);
    if(*s != 0) {
        indent -= INDENT;
        pad();
        printf("RETURN: %s\n", func);
    }
}

void trace(const char* func, const char* fmt, ...) {

    ASSERT_MSG(stack != NULL, "trace is not initialized");

    TraceState* s = peek_link_list(stack);
    if(*s != 0) {
        va_list args;

        pad();
        printf("TRACE: %s: ", func);
        va_start(args, fmt);
        vprintf(fmt, args);
        va_end(args);
        fputc('\n', stdout);
    }
}

void push_trace_state(TraceState val) {

    ASSERT_MSG(stack != NULL, "trace is not initialized");

    push_link_list(stack , _DUP_DS(&val, TraceState));
}

TraceState pop_trace_state(void) {

    ASSERT_MSG(stack != NULL, "trace is not initialized");

    TraceState* s = pop_link_list(stack);
    return *s;
}

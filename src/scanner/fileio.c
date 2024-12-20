/**
 * @file fileio.c
 *
 * @brief Handle files for applications. This is optimized for compilers.
 * Files are stored in a stack. When a file is opened, it is placed on the
 * stack and input is drawn from it. When the end of the file is reached, then
 * the file is closed and popped from the stack. Then if there is still a file
 * on the stack, then the input resumes from where it left off. When the last
 * file is popped, the input stream is closed, but the last item is not popped
 * to allow for the get_line_no() calls to return the last line that was read.
 *
 * @author Charles Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 01-12-2024
 * @copyright Copyright (c) 2024
 */
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "fileio.h"
#include "trace.h"

struct _file_ptr_ {
    FILE* fp;
    String* fname;
    int line_no;
    int col_no;
    int ch;
    struct _file_ptr_* next;
};

static struct _file_ptr_* file_stack = NULL;

/**
 * @brief Close the file on the top of the stack and pop it off of the stack,
 * making the previous file current.
 *
 */
void pop_input_file(void) {

    ENTER;
    if(file_stack != NULL) {
        fclose(file_stack->fp);
        struct _file_ptr_* tmp = file_stack;
        file_stack = tmp->next;
        destroy_string(tmp->fname);
        _FREE(tmp);
    }
    RET;
}

/**
 * @brief Open an input file and push it on the stack.
 *
 * @param fname
 */
void push_input_file(const char* fname) {

    ENTER;
    TRACE("input file: %s", fname);
    FILE* fp = fopen(fname, "r");
    if(fp == NULL) {
        fprintf(stderr, "File Error: cannot open input file: %s: %s\n", fname,
                strerror(errno));
        exit(1);
    }

    struct _file_ptr_* ptr = _ALLOC_DS(struct _file_ptr_);
    ptr->fp = fp;
    ptr->fname = create_string(fname);
    ptr->line_no = 1;
    ptr->col_no = 1;
    ptr->next = NULL;
    // prime the pump
    ptr->ch = fgetc(ptr->fp);

    // push it on the stack
    if(file_stack != NULL)
        ptr->next = file_stack;
    file_stack = ptr;
    RET;
}

/**
 * @brief Return the current char or EOF if there is no more input.
 *
 * @return int
 */
int get_char(void) {

    if(file_stack != NULL)
        return file_stack->ch;
    else
        return END_OF_INPUT;
}

/**
 * @brief Consume a character from the input stream. If the file ends, then
 * try to close it.
 *
 * @return int
 */
int consume_char(void) {

    if(file_stack != NULL) {
        if(file_stack->ch == END_OF_FILE)
            return END_OF_FILE;
        else if(file_stack->ch == '\n') {
            file_stack->line_no++;
            file_stack->col_no = 1;
        }
        else
            file_stack->col_no++;

        // note that END_OF_FILE is equal to EOF
        file_stack->ch = fgetc(file_stack->fp);
        return file_stack->ch;
    }
    else
        return END_OF_INPUT;
}

/**
 * @brief Return the line number of the current file. Returns -1 if there
 * is not currently open file.
 *
 * @return int
 */
int get_line_no(void) {

    if(file_stack != NULL)
        return file_stack->line_no;
    else
        return -1;
}

/**
 * @brief Return the column number of the current file or -1 if there is
 * no file currently open.
 *
 * @return int
 */
int get_col_no(void) {

    if(file_stack != NULL)
        return file_stack->col_no;
    else
        return -1;
}

/**
 * @brief Return the current file name as it was opened.
 *
 * @return STR
 */
const char* get_fname(void) {

    if(file_stack != NULL)
        return raw_string(file_stack->fname);
    else
        return NULL;
}

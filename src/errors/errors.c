/**
 * @file errors.c
 * @author your name (chucktilbury@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-08-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <stdarg.h>
#include "common.h"
#include "errors.h"

static int errors = 0;
static int warnings = 0;

/**
 * @brief Publish an error.
 *
 * @param type
 * @param func
 * @param fmt
 * @param ...
 */
void error(ErrorType type, Token* tok, const char* func, const char* fmt, ...) {

    va_list args;

    switch(type) {
        case ET_SYNTAX:
            fprintf(stderr, "ERROR: %s: %d: %d: ",
                    tok->fname, tok->line_no, tok->col_no);
            errors++;
            break;
        case ET_WARNING:
            fprintf(stderr, "WARNING: %s: %d: %d: ",
                    tok->fname, tok->line_no, tok->col_no);
            warnings++;
            break;
        case ET_SCANNER:
            fprintf(stderr, "SCAN ERROR: ");
            errors++;
            break;
        case ET_OTHER:
            fprintf(stderr, "OTHER: %s: ", func);
            errors++;
            break;
        case ET_FATAL:
        default:
            fprintf(stderr, "FATAL: %s: ", func);
            errors++;
            break;

    }

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fputc('\n', stderr);

    if(type == ET_FATAL || type == ET_OTHER)
        exit(1);
}

void expected(const char* str) {

    Token* tok = get_token();
    const char* got;

    switch(token_type(tok)) {
        case TOK_IDENT:
            got = raw_string(tok->str);
            break;
        default:
            got = token_to_str(tok->type);
            break;
    }

    fprintf(stderr, "ERROR: %s: %d: %d: expected %s but got '%s'",
            tok->fname, tok->line_no, tok->col_no, str, got);
    errors++;

    fputc('\n', stderr);
}

/**
 * @brief Get the errors object
 *
 * @return int
 */
int get_errors(void) {

    return errors;
}

/**
 * @brief Get the warnings object
 *
 * @return int
 */
int get_warnings(void) {

    return warnings;
}

void recover_error(void) {

    //SYNTAX("Syntax error");
    fprintf(stderr, "Syntax Error\n");
    exit(1);
}


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
                    get_scanner_fn(), get_scanner_line(), get_scanner_col());
            errors++;            
            break;
        case ET_WARNING:
            fprintf(stderr, "WARNING: %s: %d: %d: ", 
                    get_scanner_fn(), get_scanner_line(), get_scanner_col());
            warnings++;            
            break;
        case ET_SCANNER:
            fprintf(stderr, "SCAN ERROR: %s: %d: %d: ", 
                    get_scanner_fn(), get_scanner_line(), get_scanner_col());
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

    if(type == ET_FATAL || type == ET_OTHER)
        exit(1);
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


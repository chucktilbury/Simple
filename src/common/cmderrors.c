/**
 * @file errors.c
 *
 * @brief
 *
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 2024-06-17
 * @copyright Copyright (c) 2024
 *
 */
#include <stdarg.h>
#include <stdio.h>

#include "cmdline.h"

/**
 * @brief Show an error message and then show the help message and then
 * exit the program.
 *
 * @param fmt
 * @param ...
 */
void error(const char* fmt, ...) {

    va_list args;

    fprintf(stderr, "\nCMD ERROR: ");

    const char* format = (fmt[0] == '+') ? &fmt[1] : fmt;
    va_start(args, fmt);
    vfprintf(stderr, format, args);
    va_end(args);

    if(fmt[0] != '+') {
        fputs("\n", stderr);
        show_help();
    }
}

/**
 * @brief Show a warning message and continue.
 *
 * @param fmt
 * @param ...
 */
void warning(const char* fmt, ...) {

    va_list args;

    fprintf(stderr, "\nCMD WARNING: ");

    const char* format = (fmt[0] == '+') ? &fmt[1] : fmt;
    va_start(args, fmt);
    vfprintf(stderr, format, args);
    va_end(args);

    if(fmt[0] != '+') {
        fputs("\n", stderr);
    }
}

/**
 * @file errors.h
 * @author your name (chucktilbury@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-08-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef _ERRORS_H_
#define _ERRORS_H_

#include "tokens.h"

typedef enum {
    ET_SYNTAX,
    ET_WARNING,
    ET_SCANNER,
    ET_OTHER,
    ET_FATAL,
} ErrorType;

#define SYNTAX(fmt, ...) error(ET_SYNTAX, get_token(), NULL, fmt, ##__VA_ARGS__)
#define WARNING(fmt, ...) \
    error(ET_WARNING, get_token(), NULL, fmt, ##__VA_ARGS__)
#define SCANNER(fmt, ...) error(ET_SCANNER, NULL, NULL, fmt, ##__VA_ARGS__)
#define FATAL(fmt, ...) error(ET_FATAL, NULL, __func__, fmt, ##__VA_ARGS__)
#define OTHER(fmt, ...) error(ET_OTHER, NULL, __func__, fmt, ##__VA_ARGS__)
#define EXPECTED(s) expected(s)

void error(ErrorType type, Token* tok, const char* func, const char* fmt, ...);
void expected(const char* str);
int get_errors(void);
int get_warnings(void);
void recover_error(void);

#endif /* _ERRORS_H_ */

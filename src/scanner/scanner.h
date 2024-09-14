/**
 * @file scanner.h
 *
 * @brief Scanner header file. The items in this header must be implemented
 * by the scanner and the scanner queue. These routines are used directly
 * by the parser.
 *
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 01-07-2024
 * @copyright Copyright (c) 2024
 */
#ifndef _SCANNER_H_
#define _SCANNER_H_

#include "tokens.h"

/**
 * @brief Open a file for the scanner to read from. Files are expected to be
 * opened in a stack so that when a file is opened the input stream is
 * switched. Files are automatically closed when the last character is read.
 *
 * @param fname
 */
void open_file(const char* fname);

/**
 * @brief Close the current file and pop it off of the file stack.
 */
void close_file(void);

/**
 * @brief Initialize the scanner data structures. This must be called
 * before any other calls into the scanner.
 */
void init_scanner(const char* fname);

/**
 * @brief Scan a token from the input.
 *
 * @return Token*
 */
Token* scan_token(void);

#endif /* _SCANNER_H_ */

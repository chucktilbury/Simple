/**
 * @file tokens.h
 * @author your name (chucktilbury@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-08-19
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef _TOKENS_H_
#define _TOKENS_H_

/*
 * This header contains a sorted list of the actual keywords that are
 * scanned in the scanner.
 */
#include "token_defs.h"
#include "scanner.h"

#define TTYPE (token_type(get_token()))

#ifdef USE_TRACE
#include "trace.h"
#define TRACE_TOKEN                                                            \
    do {                                                                       \
        Token* t = get_token();                                                \
        TRACE("%s '%s': %d: %d: %s", token_type_to_str(t), raw_string(t->str), \
              t->line_no, t->col_no, t->fname);                                \
    } while(0)
#else
#define TRACE_TOKEN
#endif

/**
 * @brief Return the token type.
 *
 * @param tok
 * @return TokenType
 *
 */
TokenType token_type(const Token* tok);

/**
 * @brief Get the token object. This returns the current token, which is a
 * global in the scanner. If the pointer to this token needs to be referenced,
 * after advance_token() is called, then the token should be copied.
 *
 * @return Token*
 */
Token* get_token(void);

/**
 * @brief Do a deep copy of the given token pointer. All memory is duplicated.
 *
 * @param tok
 * @return Token*
 */
Token* copy_token(const Token* tok);

/**
 * @brief Make the next token in the stream the current token. This could
 * return a token that has already been read if the queue was reset, or a
 * new token could be read, depending on the state of the queue as set by
 * the other functions.
 *
 * @return Token*
 */
Token* consume_token(void);

/**
 * @brief Reset the head of the token queue to the first token that has not
 * been marked as being finalized. This actually discards the tokens that
 * have been consumed. This is called when a valid non-terminal is
 * recognized by the parser.
 */
void finalize_token_queue(void);

/**
 * @brief Reset the token queue to the state that it was in before this parser
 * function was called. This is used when the tokens that were consumed by
 * this function do not produce a valid parse. That may or may not be an
 * error. In the case of an error, this should not be called because the error
 * recovery function needs to know which tokens are involved in the error and
 * that data is captured by the flags this function undoes.
 *
 * @param tok
 */
void reset_token_queue(void* post);

/**
 * @brief Grab the current queue pointer so that it can be reset when the
 * crnt pointer moves as a result of parsing the line. This is used in
 * conjunction with reset_token_queue().
 *
 * @return void*
 */
void* post_token_queue(void);

#endif  /* _TOKENS_H_ */

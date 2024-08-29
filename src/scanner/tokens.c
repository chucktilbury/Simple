/**
 * @file tok_queue.c
 *
 * @brief This is the token queue implementation. The token queue is the
 * public interface into the scanner and it's used by the parser to
 * implement rule matching.
 *
 * NOTE: This library expects to be using garbage collection.
 *
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @version 0.0
 * @date 01-07-2024
 * @copyright Copyright (c) 2024
 */
#include "common.h"
#include "fileio.h"
#include "scanner.h"
#include "tokens.h"
#include "trace.h"

static unsigned serial = 0;
static Token end_tok;

typedef struct _tok_queue_item_ {
    Token* tok;      // the actual token pointer.
    unsigned serial; // serial number of the token.
    bool used;       // When the token has been finalized in a rule.
    struct _tok_queue_item_* next;
} TokQueueItem;

typedef struct {
    TokQueueItem* head;
    TokQueueItem* crnt;
    TokQueueItem* tail;
} TokQueue;

// static TokQueue* tqueue = NULL;
static LinkList* tqueue_stack = NULL;

/*
 * Append a token to the end of the queue. It could be that advance_token()
 * has found the end of the queue, but it could be something else.
 */
void append_token(Token* tok) {

    TokQueue* tqueue = peek_link_list(tqueue_stack);
    ASSERT(tqueue != NULL);
    ASSERT(tok != NULL);

    TokQueueItem* item;

    item         = _ALLOC_DS(TokQueueItem);
    item->tok    = copy_token(tok);
    item->serial = serial++;
    item->used   = false;

    if(tqueue->tail != NULL) {
        tqueue->tail->next = item;
        tqueue->tail       = item;
    }
    else {
        tqueue->head = item;
        tqueue->crnt = item;
        tqueue->tail = item;
    }
}

/**
 * @brief Push the token queue.
 *
 *
 */
void push_token_queue(void) {

    TokQueue* queue = _ALLOC_DS(TokQueue);
    push_link_list(tqueue_stack, queue);
    append_token(scan_token());
}

/**
 * @brief Pop the token queue
 *
 *
 */
void pop_token_queue(void) {

    pop_link_list(tqueue_stack);
}

/**
 * @brief Open a file for the scanner to read from. Files are expected to be
 * opened in a stack so that when a file is opened the input stream is
 * switched. Files are automatically closed when the last character is read.
 *
 * @param fname
 */
void open_file(const char* fname) {

    ENTER;

    if(tqueue_stack == NULL)
        tqueue_stack = create_link_list();

    push_input_file(fname);
    push_token_queue();

    RET;
}

/**
 * @brief Close the current file and pop it off of the file stack.
 */
void close_file(void) {

    ENTER;
    pop_input_file();
    pop_link_list(tqueue_stack);
    RET;
}

/**
 * @brief Return the token type safely.
 * 
 * @param tok 
 * @return TokenType 
 */
TokenType token_type(Token* tok) {

    if(tok != NULL)
        return tok->type;
    else
        return TOK_END_OF_INPUT;
} 

/**
 * @brief Get the token object. This returns the current token, which is a
 * global in the scanner. If the value of this token needs to be preserved,
 * then the token should be copied.
 *
 * @return Token*
 */
Token* get_token(void) {

    TokQueue* tqueue = peek_link_list(tqueue_stack);
    if(tqueue == NULL) {
        end_tok.type = TOK_END_OF_INPUT;
        RETURN(&end_tok);
    }

    if(tqueue->crnt != NULL) {
        return tqueue->crnt->tok;
    }

    // Should never happen. Will probably cause a segfault.
    return NULL;
}

/**
 * @brief Do a deep copy of the given token pointer. All memory is duplicated.
 *
 * @param tok
 * @return Token*
 */
Token* copy_token(const Token* tok) {

    ASSERT(tok != NULL);

    Token* ntok;

    ntok          = _ALLOC_DS(Token);
    ntok->fname   = _DUP_STR(tok->fname);
    ntok->str     = copy_string(tok->str);
    ntok->line_no = tok->line_no;
    ntok->col_no  = tok->col_no;
    ntok->type    = tok->type;

    return ntok;
}

/**
 * @brief Make the next token in the stream the current token. If the token
 * before this one was the end of the input, then nothing happens and the
 * returned token is the end of input token. Returns the current token
 * after the advance happens.
 *
 * @return Token*
 */
Token* consume_token(void) {

    ENTER;
    TRACE_TOKEN;

    TokQueue* tqueue = peek_link_list(tqueue_stack);
    if(tqueue == NULL) {
        end_tok.type = TOK_END_OF_INPUT;
        RETURN(&end_tok);
    }

    ASSERT(tqueue->crnt != NULL);

    if(tqueue->crnt->tok->type != TOK_END_OF_INPUT) {
        if(tqueue->crnt->next == NULL)
            append_token(scan_token());

        tqueue->crnt = tqueue->crnt->next;
    }

    RETURN(tqueue->crnt->tok);
}

/**
 * @brief After a rule is parsed, this function sets the head of the token
 * queue to the first unused token. All of the tokens that have been used
 * are discarded and collected by the garbage collector.
 */
void finalize_token_queue(void) {

    ENTER;

    TokQueue* tqueue = peek_link_list(tqueue_stack);
    tqueue->head     = tqueue->crnt;

    RET;
}

void kill_token_queue(void) {

    ENTER;

    TokQueue* tqueue = peek_link_list(tqueue_stack);
    tqueue->head     = NULL;
    tqueue->crnt     = NULL;
    tqueue->tail     = NULL;
    append_token(scan_token());

    RET;
}

/**
 * @brief Grab the current queue pointer so that it can be reset when the
 * crnt pointer moves as a result of parsing the line. This is used in
 * conjunction with reset_token_queue(). This should be called and the pointer
 * saved at the beginning of any parser routine that expects alternatives.
 *
 * @return void*
 *
 */
void* post_token_queue(void) {

    ENTER;
    TokQueue* tqueue = peek_link_list(tqueue_stack);
    ASSERT(tqueue != NULL);
    RETURN((void*)tqueue->crnt);
}

/**
 * @brief Reset the token stream to the beginning. This is used when a rule
 * could not be matched and the token stream needs to be rewound to test
 * the next rule in a list of alternatives. Call this when a parser
 * alternative fails in order to reset the crnt pointer.
 *
 * @return Token*
 */
void reset_token_queue(void* post) {

    ENTER;

    // if(!get_recovery_state()) {
        TRACE("recover the queue");
        TokQueue* tqueue = peek_link_list(tqueue_stack);
        ASSERT(tqueue != NULL);

        tqueue->crnt = (TokQueueItem*)post;
    // }
    RET;
}

// void dump_token_queue(void) {

//     TokQueue* tqueue = peek_link_list(tqueue_stack);
//     ASSERT(tqueue != NULL);
//     ASSERT(tqueue->head != NULL);

//     for(TokQueueItem* crnt = tqueue->head; crnt != NULL; crnt = crnt->next) {
//         print_terminal(crnt->tok);
//         fputc('\n', stdout);
//     }
// }

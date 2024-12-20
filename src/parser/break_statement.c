/**
 *
 * @file break_statement.c
 *
 * @brief Parse grammar production break_statement.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "common.h"
#include "errors.h"
#include "parser.h"
#include "tokens.h"

/**
 *
 * Grammar production:
 *
 * break_statement
 *     : 'break'
 *     ;
 */
ast_break_statement_t* parse_break_statement(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_break_statement_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE;
                if(TOK_BREAK == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_break_statement_t*)create_ast_node(AST_BREAK_STATEMENT);
                finished = true;
                break;

            case 101:
                // not a match, not an error
                TRACE_STATE;
                reset_token_queue(post);
                finished = true;
                break;

            case 102:
                // error found
                TRACE_STATE;
                recover_error();
                finished = true;
                break;

            default:
                FATAL("unknown state: %d", state);
        }
    }

    RETURN(node);
}

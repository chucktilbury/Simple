/**
 *
 * @file continue_statement.c
 *
 * @brief Parse grammar production continue_statement.
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
 * continue_statement
 *     : 'continue'
 *     ;
 */
ast_continue_statement_t* parse_continue_statement(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_continue_statement_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                if(TOK_CONTINUE == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else
                    state = 101;
                TRACE_STATE;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_continue_statement_t*)create_ast_node(AST_CONTINUE_STATEMENT);
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

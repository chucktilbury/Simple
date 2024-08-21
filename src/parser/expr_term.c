/**
 *
 * @file expr_term.c
 *
 * @brief Parse grammar production expr_term.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "common.h"
#include "tokens.h"
#include "errors.h"
#include "parser.h"

/**
 *
 * Grammar production:
 *
 * expr_term
 *     : expr_factor '+' expr_factor
 *     | expr_factor '-' expr_factor
 *     ;
 */
ast_expr_term_t* parse_expr_term(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_expr_term_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE(state);
                break;

            case 100:
                // production recognized
                TRACE_STATE(state);
                node = (ast_expr_term_t*)create_ast_node(AST_EXPR_TERM);
                finished = true;
                break;

            case 101:
                // not a match, not an error
                TRACE_STATE(state);
                reset_token_queue(post);
                finished = true;
                break;

            case 102:
                // error found
                TRACE_STATE(state);
                recover_error();
                finished = true;
                break;

            default:
                FATAL("unknown state: %d", state);
        }
    }

    RETURN(node);
}


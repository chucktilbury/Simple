/**
 *
 * @file expr_primary.c
 *
 * @brief Parse grammar production expr_primary.
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
 * expr_primary
 *     : literal_value
 *     | compound_reference
 *     | cast_statement
 *     | '(' expression ')'
 *     ;
 */
ast_expr_primary_t* parse_expr_primary(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_expr_primary_t* node = NULL;
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
                node = (ast_expr_primary_t*)create_ast_node(AST_EXPR_PRIMARY);
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


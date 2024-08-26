/**
 *
 * @file var_decl_list.c
 *
 * @brief Parse grammar production var_decl_list.
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
 * var_decl_list
 *     : '(' ( var_decl ( ',' var_decl )* )? ')'
 *     ;
 */
ast_var_decl_list_t* parse_var_decl_list(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_var_decl_list_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_var_decl_list_t*)create_ast_node(AST_VAR_DECL_LIST);
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


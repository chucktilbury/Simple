/**
 *
 * @file assign_inc_item.c
 *
 * @brief Parse grammar production assign_inc_item.
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
 * assign_inc_item
 *     : expression
 *     | string_literal
 *     ;
 */
ast_assign_inc_item_t* parse_assign_inc_item(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_assign_inc_item_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_node_t* ptr;

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE(state);
                if(NULL != (ptr = (ast_node_t*)parse_expression(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_string_literal(pstate)))
                    state = 100;
                else
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE(state);
                node = (ast_assign_inc_item_t*)create_ast_node(AST_ASSIGN_INC_ITEM);
                node->ptr = ptr;
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


/**
 *
 * @file assignment_item.c
 *
 * @brief Parse grammar production assignment_item.
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
 * assignment_item
 *     : expression
 *     | list_init
 *     ;
 */
ast_assignment_item_t* parse_assignment_item(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_assignment_item_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_node_t* ptr = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE;
                if(NULL != (ptr = (ast_node_t*)parse_list_init(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_expression(pstate)))
                    state = 100;
                else
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_assignment_item_t*)create_ast_node(AST_ASSIGNMENT_ITEM);
                node->ptr = ptr;
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

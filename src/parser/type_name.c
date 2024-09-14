/**
 *
 * @file type_name.c
 *
 * @brief Parse grammar production type_name.
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
 * type_name
 *     : literal_type_name
 *     | compound_name
 *     ;
 */
ast_type_name_t* parse_type_name(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_type_name_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_node_t* ptr = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE;
                if(NULL != (ptr = (ast_node_t*)parse_literal_type_name(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_compound_name(pstate)))
                    state = 100;
                else
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_type_name_t*)create_ast_node(AST_TYPE_NAME);
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

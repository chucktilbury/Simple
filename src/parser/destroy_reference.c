/**
 *
 * @file destroy_reference.c
 *
 * @brief Parse grammar production destroy_reference.
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
 * destroy_reference
 *     : destroy_name
 *     ;
 */
ast_destroy_reference_t* parse_destroy_reference(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_destroy_reference_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_destroy_name_t* name = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(NULL != (name = parse_destroy_name(pstate)))
                    state = 100;
                else
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_destroy_reference_t*)create_ast_node(AST_DESTROY_REFERENCE);
                node->name = name;
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


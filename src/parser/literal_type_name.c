/**
 *
 * @file literal_type_name.c
 *
 * @brief Parse grammar production literal_type_name.
 * This file was generated on Wed Aug 21 09:35:58 2024.
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
 * literal_type_name
 *     : 'float'
 *     | 'integer'
 *     | 'string'
 *     | 'boolean'
 *     | 'nothing'
 *     | 'list'
 *     | 'dict'
 *     ;
 */
ast_literal_type_name_t* parse_literal_type_name(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_literal_type_name_t* node = NULL;
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
                node = (ast_literal_type_name_t*)create_ast_node(AST_LITERAL_TYPE_NAME);
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


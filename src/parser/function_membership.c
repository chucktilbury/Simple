/**
 * @file function_membership.c
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-09-13
 *
 * @copyright Copyright (c) 2024
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
 * function_membership
 *     : compound_name ':'
 *     ;
 */
ast_function_membership_t* parse_function_membership(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_function_membership_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_compound_name_t* name = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(NULL != (name = parse_compound_name(pstate)))
                    state = 1;
                else
                    state = 101;
                break;

            case 1:
                TRACE_STATE;
                if(TOK_COLON == TTYPE) {
                    consume_token();
                    state = 100;
                }
                else
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_function_membership_t*)create_ast_node(AST_FUNCTION_MEMBERSHIP);
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

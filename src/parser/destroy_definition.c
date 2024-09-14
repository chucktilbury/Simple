/**
 *
 * @file destroy_definition.c
 *
 * @brief Parse grammar production destroy_definition.
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
 * destroy_definition
 *     : ( function_membership )? 'destroy' ( function_body )?
 *     ;
 */
ast_destroy_definition_t* parse_destroy_definition(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_destroy_definition_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_function_membership_t* member = NULL;
    ast_function_body_t* body = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                // optional membership
                TRACE_STATE;
                member = parse_function_membership(pstate);
                state = 1;
                break;

            case 1:
                TRACE_STATE;
                if(TOK_DESTROY == TTYPE) {
                    consume_token();
                    state = 2;
                }
                else 
                    // could be destroy or something else, even if member != NULL
                    state = 101;
                break;

            case 2:
                TRACE_STATE;
                if(NULL != (body = parse_function_body(pstate)))
                    state = 100;
                else {
                    EXPECTED("a function body");
                    state = 102;
                }
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_destroy_definition_t*)create_ast_node(AST_DESTROY_DEFINITION);
                node->member = member;
                node->body = body;
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


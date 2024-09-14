/**
 *
 * @file create_definition.c
 *
 * @brief Parse grammar production create_definition.
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
 * create_definition
 *     : ( function_membership )? 'create' func_parm_decl_list ( function_body )?
 *     ;
 */
ast_create_definition_t* parse_create_definition(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_create_definition_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_function_membership_t* member = NULL;
    ast_func_parm_decl_list_t* inp = NULL;
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
                if(TOK_CREATE == TTYPE) {
                    consume_token();
                    state = 2;
                }
                else
                    // could be destroy or something else, even if member != NULL
                    state = 101;
                break;

            case 2:
                TRACE_STATE;
                if(NULL != (inp = parse_func_parm_decl_list(pstate)))
                    state = 3;
                else {
                    EXPECTED("the function parameter list");
                    state = 102;
                }
                break;

            case 3:
                // optional function body
                TRACE_STATE;
                body = parse_function_body(pstate);
                state = 100;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_create_definition_t*)create_ast_node(AST_CREATE_DEFINITION);
                node->member = member;
                node->inp = inp;
                node->inp->inout = true;
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

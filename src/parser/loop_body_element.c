/**
 *
 * @file loop_body_element.c
 *
 * @brief Parse grammar production loop_body_element.
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
 * loop_body_element
 *     : function_body_element
 *     | break_statement
 *     | continue_statement
 *     | yield_statement
 *     | loop_body
 *     ;
 */
ast_loop_body_element_t* parse_loop_body_element(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_loop_body_element_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_node_t* ptr = NULL;
    Token* inl = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(NULL != (ptr = (ast_node_t*)parse_function_body_element(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_break_statement(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_continue_statement(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_yield_statement(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_loop_body(pstate)))
                    state = 100;
                else
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_loop_body_element_t*)create_ast_node(AST_LOOP_BODY_ELEMENT);
                node->ptr = ptr;
                node->inl = inl;
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


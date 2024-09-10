/**
 *
 * @file function_body_element.c
 *
 * @brief Parse grammar production function_body_element.
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
 * function_body_element
 *     : var_definition
 *     | function_reference
 *     | create_reference
 *     | destroy_reference
 *     | assignment
 *     | while_clause
 *     | do_clause
 *     | for_clause
 *     | if_clause
 *     | try_clause
 *     | switch_clause
 *     | break_statement
 *     | continue_statement
 *     | INLINE
 *     | yield_statement
 *     | type_statement
 *     | return_statement
 *     | raise_statement
 *     | trace_statement
 *     | print_statement
 *     | function_body
 *     ;
 */
ast_function_body_element_t* parse_function_body_element(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_function_body_element_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_node_t* ptr = NULL;
    Token* inl = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                TRACE_STATE;
                if(NULL != (ptr = (ast_node_t*)parse_var_definition(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_function_reference(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_create_reference(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_destroy_reference(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_assignment(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_while_clause(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_do_clause(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_for_clause(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_if_clause(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_try_clause(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_type_statement(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_return_statement(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_raise_statement(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_trace_statement(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_print_statement(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_exit_statement(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_function_body(pstate)))
                    state = 100;
                else if(TOK_INLINE == TTYPE) {
                    inl = copy_token(get_token());
                    consume_token();
                    state = 100;
                }
                else
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_function_body_element_t*)create_ast_node(AST_FUNCTION_BODY_ELEMENT);
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


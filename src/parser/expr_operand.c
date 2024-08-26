/**
 *
 * @file expr_operand.c
 *
 * @brief Parse grammar production expr_primary.
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
 * expr_operand
 *     : literal_value
 *     | compound_reference
 *     | cast_statement
 *     ;
 */
ast_expr_operand_t* parse_expr_operand(parser_state_t* pstate) {

    ASSERT(pstate != NULL);
    ENTER;

    ast_expr_operand_t* node = NULL;
    int state = 0;
    bool finished = false;
    void* post = post_token_queue();

    ast_node_t* ptr = NULL;

    while(!finished) {
        switch(state) {
            case 0:
                // initial state
                TRACE_STATE;
                if(NULL != (ptr = (ast_node_t*)parse_literal_value(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_compound_reference(pstate)))
                    state = 100;
                else if(NULL != (ptr = (ast_node_t*)parse_cast_statement(pstate)))
                    state = 100;
                else
                    state = 101;
                break;

            case 100:
                // production recognized
                TRACE_STATE;
                node = (ast_expr_operand_t*)create_ast_node(AST_EXPR_OPERAND);
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


/**
 *
 * @file loop_body_element.c
 *
 * @brief Traverse AST for node loop_body_element.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "ast.h"
#include "common.h"
#include "errors.h"
#include "trace.h"

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
void traverse_loop_body_element(ast_loop_body_element_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    if(node->inl != NULL) {
        TRACE_TERMINAL(node->inl);
    }
    else {
        switch(nterm_type(node->ptr)) {
            case AST_FUNCTION_BODY_ELEMENT:
                traverse_function_body_element((ast_function_body_element_t*)(node->ptr),
                                               pre, post);
                break;
            case AST_BREAK_STATEMENT:
                traverse_break_statement((ast_break_statement_t*)(node->ptr), pre, post);
                break;
            case AST_CONTINUE_STATEMENT:
                traverse_continue_statement((ast_continue_statement_t*)(node->ptr),
                                            pre, post);
                break;
            case AST_YIELD_STATEMENT:
                traverse_yield_statement((ast_yield_statement_t*)(node->ptr), pre, post);
                break;
            case AST_LOOP_BODY:
                traverse_loop_body((ast_loop_body_t*)(node->ptr), pre, post);
                break;
            default:
                FATAL("unknown ast node type: %s", nterm_type_to_str(node->ptr));
        }
    }

    CALL_NODE_FUNC(post);
    RET;
}

/**
 *
 * @file function_body_element.c
 *
 * @brief Traverse AST for node function_body_element.
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
 *     | break_statement
 *     | exit_statement
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
void traverse_function_body_element(ast_function_body_element_t* node,
                                    AstFuncPtr pre,
                                    AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    if(node->inl != NULL) {
        TRACE_TERMINAL(node->inl);
    }
    else {
        switch(nterm_type(node->ptr)) {
            case AST_VAR_DEFINITION:
                traverse_var_definition((ast_var_definition_t*)(node->ptr), pre, post);
                break;
            case AST_FUNCTION_REFERENCE:
                traverse_function_reference((ast_function_reference_t*)(node->ptr),
                                            pre, post);
                break;
            case AST_CREATE_REFERENCE:
                traverse_create_reference((ast_create_reference_t*)(node->ptr), pre, post);
                break;
            case AST_DESTROY_REFERENCE:
                traverse_destroy_reference((ast_destroy_reference_t*)(node->ptr), pre, post);
                break;
            case AST_ASSIGNMENT:
                traverse_assignment((ast_assignment_t*)(node->ptr), pre, post);
                break;
            case AST_WHILE_CLAUSE:
                traverse_while_clause((ast_while_clause_t*)(node->ptr), pre, post);
                break;
            case AST_DO_CLAUSE:
                traverse_do_clause((ast_do_clause_t*)(node->ptr), pre, post);
                break;
            case AST_FOR_CLAUSE:
                traverse_for_clause((ast_for_clause_t*)(node->ptr), pre, post);
                break;
            case AST_IF_CLAUSE:
                traverse_if_clause((ast_if_clause_t*)(node->ptr), pre, post);
                break;
            case AST_TRY_CLAUSE:
                traverse_try_clause((ast_try_clause_t*)(node->ptr), pre, post);
                break;
            case AST_BREAK_STATEMENT:
                traverse_break_statement((ast_break_statement_t*)(node->ptr), pre, post);
                break;
            case AST_EXIT_STATEMENT:
                traverse_exit_statement((ast_exit_statement_t*)(node->ptr), pre, post);
                break;
            case AST_CONTINUE_STATEMENT:
                traverse_continue_statement((ast_continue_statement_t*)(node->ptr),
                                            pre, post);
                break;
            case AST_YIELD_STATEMENT:
                traverse_yield_statement((ast_yield_statement_t*)(node->ptr), pre, post);
                break;
            case AST_TYPE_STATEMENT:
                traverse_type_statement((ast_type_statement_t*)(node->ptr), pre, post);
                break;
            case AST_RETURN_STATEMENT:
                traverse_return_statement((ast_return_statement_t*)(node->ptr), pre, post);
                break;
            case AST_RAISE_STATEMENT:
                traverse_raise_statement((ast_raise_statement_t*)(node->ptr), pre, post);
                break;
            case AST_TRACE_STATEMENT:
                traverse_trace_statement((ast_trace_statement_t*)(node->ptr), pre, post);
                break;
            case AST_PRINT_STATEMENT:
                traverse_print_statement((ast_print_statement_t*)(node->ptr), pre, post);
                break;
            case AST_FUNCTION_BODY:
                traverse_function_body((ast_function_body_t*)(node->ptr), pre, post);
                break;
            default:
                FATAL("unknown ast node type: %s", nterm_type_to_str(node->ptr));
        }
    }

    CALL_NODE_FUNC(post);
    RET;
}

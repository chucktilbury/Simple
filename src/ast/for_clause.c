/**
 *
 * @file for_clause.c
 *
 * @brief Traverse AST for node for_clause.
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
 * for_clause
 *     : 'for' ( '(' ( expression 'as' IDENT )? ')' )? function_body
 *     ;
 */
void traverse_for_clause(ast_for_clause_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    if(node->ident != NULL) {
        TRACE_TERMINAL(node->ident);
        traverse_expression(node->expr, pre, post);
    }
    traverse_loop_body(node->body, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}

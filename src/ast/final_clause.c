/**
 *
 * @file final_clause.c
 *
 * @brief Traverse AST for node final_clause.
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
 * final_clause
 *     : 'final' '(' IDENT ')' function_body
 *     ;
 */
void traverse_final_clause(ast_final_clause_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    TRACE_TERMINAL(node->id1);
    traverse_function_body(node->body, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}

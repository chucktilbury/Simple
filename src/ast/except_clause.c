/**
 *
 * @file except_clause.c
 *
 * @brief Traverse AST for node except_clause.
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
 * except_clause
 *     : 'except' '(' IDENT ',' IDENT ')' function_body
 *     ;
 */
void traverse_except_clause(ast_except_clause_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    TRACE_TERMINAL(node->id1);
    TRACE_TERMINAL(node->id2);
    traverse_function_body(node->body, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}

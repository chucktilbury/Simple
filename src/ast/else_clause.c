/**
 *
 * @file else_clause.c
 *
 * @brief Traverse AST for node else_clause.
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
 * else_clause
 *     : 'else' '(' expression ')' function_body
 *     ;
 */
void traverse_else_clause(ast_else_clause_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    traverse_expression(node->expr, pre, post);
    traverse_function_body(node->body, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}

/**
 *
 * @file else_clause.c
 *
 * @brief Traverse AST for node else_clause.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

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

    CALL_NODE_FUNC(post);
    RET;
}


/**
 *
 * @file while_clause.c
 *
 * @brief Traverse AST for node while_clause.
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
 * while_clause
 *     : while_definition function_body
 *     ;
 */
void traverse_while_clause(ast_while_clause_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    traverse_while_definition(node->expr, pre, post);
    traverse_loop_body(node->body, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


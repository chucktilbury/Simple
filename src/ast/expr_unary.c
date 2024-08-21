/**
 *
 * @file expr_unary.c
 *
 * @brief Traverse AST for node expr_unary.
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
 * expr_unary
 *     : '-' expr_primary
 *     | '!' expr_primary
 *     ;
 */
void traverse_expr_unary(ast_expr_unary_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


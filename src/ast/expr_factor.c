/**
 *
 * @file expr_factor.c
 *
 * @brief Traverse AST for node expr_factor.
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
 * expr_factor
 *     : expr_unary '*' expr_unary
 *     | expr_unary '/' expr_unary
 *     | expr_unary '%' expr_unary
 *     ;
 */
void traverse_expr_factor(ast_expr_factor_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


/**
 *
 * @file expr_equality.c
 *
 * @brief Traverse AST for node expr_equality.
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
 * expr_equality
 *     : expr_compare '==' expr_compare
 *     | expr_compare '!=' expr_compare
 *     ;
 */
void traverse_expr_equality(ast_expr_equality_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


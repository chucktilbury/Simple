/**
 *
 * @file expr_or.c
 *
 * @brief Traverse AST for node expr_or.
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
 * expr_or
 *     : expr_and 'or' expr_and
 *     ;
 */
void traverse_expr_or(ast_expr_or_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


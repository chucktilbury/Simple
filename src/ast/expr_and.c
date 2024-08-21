/**
 *
 * @file expr_and.c
 *
 * @brief Traverse AST for node expr_and.
 * This file was generated on Wed Aug 21 09:35:58 2024.
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
 * expr_and
 *     : expr_equality 'and' expr_equality
 *     ;
 */
void traverse_expr_and(ast_expr_and_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


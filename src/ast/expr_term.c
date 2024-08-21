/**
 *
 * @file expr_term.c
 *
 * @brief Traverse AST for node expr_term.
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
 * expr_term
 *     : expr_factor '+' expr_factor
 *     | expr_factor '-' expr_factor
 *     ;
 */
void traverse_expr_term(ast_expr_term_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


/**
 *
 * @file expr_compare.c
 *
 * @brief Traverse AST for node expr_compare.
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
 * expr_compare
 *     : expr_term '<' expr_term
 *     | expr_term '>' expr_term
 *     | expr_term '<=' expr_term
 *     | expr_term '>=' expr_term
 *     ;
 */
void traverse_expr_compare(ast_expr_compare_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


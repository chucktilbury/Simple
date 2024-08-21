/**
 *
 * @file expr_primary.c
 *
 * @brief Traverse AST for node expr_primary.
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
 * expr_primary
 *     : literal_value
 *     | compound_reference
 *     | cast_statement
 *     | '(' expression ')'
 *     ;
 */
void traverse_expr_primary(ast_expr_primary_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


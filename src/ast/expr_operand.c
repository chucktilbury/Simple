/**
 *
 * @file expr_primary.c
 *
 * @brief Traverse AST for node expr_primary.
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
 * expr_operand
 *     : literal_value
 *     | compound_reference
 *     | cast_statement
 *     | '(' expression ')'
 *     ;
 */
void traverse_expr_operand(ast_expr_operand_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

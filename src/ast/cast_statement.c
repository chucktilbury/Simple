/**
 *
 * @file cast_statement.c
 *
 * @brief Traverse AST for node cast_statement.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "ast.h"
#include "common.h"
#include "errors.h"
#include "trace.h"

/**
 *
 * Grammar production:
 *
 * cast_statement
 *     : type_name ':' expression
 *     ;
 */
void traverse_cast_statement(ast_cast_statement_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    traverse_type_name(node->type, pre, post);
    traverse_expression(node->expr, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}

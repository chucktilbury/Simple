/**
 *
 * @file trace_statement.c
 *
 * @brief Traverse AST for node trace_statement.
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
 * trace_statement
 *     : 'trace' '(' string_literal ')'
 *     ;
 */
void traverse_trace_statement(ast_trace_statement_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    traverse_string_literal(node->str, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


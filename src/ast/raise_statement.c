/**
 *
 * @file raise_statement.c
 *
 * @brief Traverse AST for node raise_statement.
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
 * raise_statement
 *     : 'raise' '(' IDENT ',' string_literal ')'
 *     ;
 */
void traverse_raise_statement(ast_raise_statement_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    TRACE_TERMINAL(node->id);
    traverse_string_literal(node->str, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


/**
 *
 * @file operator.c
 *
 * @brief Traverse AST for node operator.
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
 * expr_operator
 *     : '+' | '-' | '*' | '/' | '%' | '|' | '&' | '!'
 *     | '==' | '!=' | '<' | '>' | '<=' | '>='
 *     | 'or' | 'and' | 'not' | 'equ' | 'nequ'
 *     | 'lt' | 'gt' | 'lte' | 'gte'
 *     ;
 */
void traverse_expr_operator(ast_expr_operator_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    TRACE_TERMINAL(node->oper);

    CALL_NODE_FUNC(post);
    RET;
}

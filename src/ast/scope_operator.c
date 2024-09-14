/**
 *
 * @file scope_operator.c
 *
 * @brief Traverse AST for node scope_operator.
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
 * scope_operator
 *     : 'private'
 *     | 'public'
 *     | 'protected'
 *     ;
 */
void traverse_scope_operator(ast_scope_operator_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    TRACE_TERMINAL(node->tok);

    CALL_NODE_FUNC(post);
    RET;
}

/**
 *
 * @file yield_statement.c
 *
 * @brief Traverse AST for node yield_statement.
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
 * yield_statement
 *     : 'yield' '(' compound_reference ')'
 *     ;
 */
void traverse_yield_statement(ast_yield_statement_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    traverse_compound_reference(node->arg, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


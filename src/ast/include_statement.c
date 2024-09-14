/**
 *
 * @file include_statement.c
 *
 * @brief Traverse AST for node include_statement.
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
 * include_statement
 *     : 'include' formatted_strg
 *     ;
 */
void traverse_include_statement(ast_include_statement_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    traverse_formatted_strg(node->str, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}

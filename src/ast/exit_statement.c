/**
 *
 * @file exit_statement.c
 *
 * @brief Traverse AST for node exit_statement.
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
 * exit_statement
 *     : 'exit' '(' expression ')'
 *     ;
 */
void traverse_exit_statement(ast_exit_statement_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}

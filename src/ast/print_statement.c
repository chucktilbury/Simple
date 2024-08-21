/**
 *
 * @file print_statement.c
 *
 * @brief Traverse AST for node print_statement.
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
 * print_statement
 *     : 'print' ( expression_list )?
 *     ;
 */
void traverse_print_statement(ast_print_statement_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


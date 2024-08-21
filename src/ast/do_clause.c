/**
 *
 * @file do_clause.c
 *
 * @brief Traverse AST for node do_clause.
 * This file was generated on Wed Aug 21 09:35:58 2024.
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
 * do_clause
 *     : 'do' function_body while_definition
 *     ;
 */
void traverse_do_clause(ast_do_clause_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


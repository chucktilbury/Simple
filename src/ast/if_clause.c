/**
 *
 * @file if_clause.c
 *
 * @brief Traverse AST for node if_clause.
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
 * if_clause
 *     : 'if' '(' expression ')' function_body ( else_clause )* ( final_else_clause )?
 *     ;
 */
void traverse_if_clause(ast_if_clause_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


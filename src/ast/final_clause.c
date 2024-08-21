/**
 *
 * @file final_clause.c
 *
 * @brief Traverse AST for node final_clause.
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
 * final_clause
 *     : 'final' '(' IDENT ')' function_body
 *     ;
 */
void traverse_final_clause(ast_final_clause_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


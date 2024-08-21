/**
 *
 * @file try_clause.c
 *
 * @brief Traverse AST for node try_clause.
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
 * try_clause
 *     : 'try' function_body ( except_clause )* ( final_clause )?
 *     ;
 */
void traverse_try_clause(ast_try_clause_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


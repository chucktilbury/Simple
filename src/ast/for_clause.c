/**
 *
 * @file for_clause.c
 *
 * @brief Traverse AST for node for_clause.
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
 * for_clause
 *     : 'for' ( '(' ( (type_name)? IDENT 'in' expression )? ')' )? function_body
 *     ;
 */
void traverse_for_clause(ast_for_clause_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


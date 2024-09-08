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

    traverse_expression(node->expr, pre, post);
    traverse_function_body(node->body, pre, post);

    ast_else_clause_t* ec;
    int mark = 0;

    while(NULL != (ec = iterate_ptr_lst(node->ecl, &mark)))
        traverse_else_clause(ec, pre, post);

    if(node->fecl != NULL)
        traverse_final_else_clause(node->fecl, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


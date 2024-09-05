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

    traverse_function_body(node->body, pre, post);

    ast_except_clause_t* ec;
    int mark = 0;

    while(NULL != (ec = iterate_ptr_lst(node->list, &mark)))
        traverse_except_clause(ec, pre, post);

    traverse_final_clause(node->fin, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


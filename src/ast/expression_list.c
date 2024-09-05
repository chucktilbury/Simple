/**
 *
 * @file expression_list.c
 *
 * @brief Traverse AST for node expression_list.
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
 * expression_list
 *     : '(' (expression ( ',' expression )*)? ')'
 *     ;
 */
void traverse_expression_list(ast_expression_list_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    ast_expression_t* ex; 
    int mark = 0;

    while(NULL != (ex = iterate_ptr_lst(node->list, &mark)))
        traverse_expression(ex, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


/**
 *
 * @file expression_list.c
 *
 * @brief Traverse AST for node expression_list.
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
 * expression_list
 *     : '(' (expression ( ',' expression )*)? ')'
 *     ;
 */
void traverse_expression_list(ast_expression_list_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


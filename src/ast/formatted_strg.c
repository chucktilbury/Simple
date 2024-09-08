/**
 *
 * @file formatted_strg.c
 *
 * @brief Traverse AST for node formatted_strg.
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
 * formatted_strg
 *     : LITERAL_DSTR ( expression_list )?
 *     ;
 */
void traverse_formatted_strg(ast_formatted_strg_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    TRACE_TERMINAL(node->str);

    if(node->exprs != NULL)
        traverse_expression_list(node->exprs, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


/**
 *
 * @file array_param.c
 *
 * @brief Traverse AST for node array_param.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "ast.h"
#include "common.h"
#include "errors.h"
#include "trace.h"

/**
 *
 * Grammar production:
 *
 * array_param
 *     : '[' array_param_item ']'
 *     ;
 */
void traverse_array_param(ast_array_param_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    traverse_array_param_item(node->item, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}

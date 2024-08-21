/**
 *
 * @file array_param_item.c
 *
 * @brief Traverse AST for node array_param_item.
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
 * array_param_item
 *     : expression
 *     | string_literal
 *     ;
 */
void traverse_array_param_item(ast_array_param_item_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


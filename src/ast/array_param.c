/**
 *
 * @file array_param.c
 *
 * @brief Traverse AST for node array_param.
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
 * array_param
 *     : '[' array_param_item ']'
 *     ;
 */
void traverse_array_param(ast_array_param_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


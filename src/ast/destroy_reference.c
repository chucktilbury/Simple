/**
 *
 * @file destroy_reference.c
 *
 * @brief Traverse AST for node destroy_reference.
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
 * destroy_reference
 *     : destroy_name
 *     ;
 */
void traverse_destroy_reference(ast_destroy_reference_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


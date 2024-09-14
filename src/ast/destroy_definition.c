/**
 *
 * @file destroy_definition.c
 *
 * @brief Traverse AST for node destroy_definition.
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
 * destroy_definition
 *     : ( function_membership )? 'destroy' ( function_body )?
 *     ;
 */
void traverse_destroy_definition(ast_destroy_definition_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    if(node->member != NULL)
        traverse_function_membership(node->member, pre, post);
    if(node->body != NULL)
        traverse_function_body(node->body, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


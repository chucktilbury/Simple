/**
 *
 * @file destroy_definition.c
 *
 * @brief Traverse AST for node destroy_definition.
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
 * destroy_definition
 *     : ('virtual' )? destroy_name function_body
 *     ;
 */
void traverse_destroy_definition(ast_destroy_definition_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


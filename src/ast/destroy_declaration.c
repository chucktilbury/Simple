/**
 *
 * @file destroy_declaration.c
 *
 * @brief Traverse AST for node destroy_declaration.
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
 * destroy_declaration
 *     : ('virtual' )? 'destroy'
 *     ;
 */
void traverse_destroy_declaration(ast_destroy_declaration_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    TRACE("is_virtual = %s", node->is_virtual? "true": "false");

    CALL_NODE_FUNC(post);
    RET;
}


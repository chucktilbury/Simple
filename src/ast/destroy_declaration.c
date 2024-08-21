/**
 *
 * @file destroy_declaration.c
 *
 * @brief Traverse AST for node destroy_declaration.
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
 * destroy_declaration
 *     : ('virtual' )? 'destroy'
 *     ;
 */
void traverse_destroy_declaration(ast_destroy_declaration_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


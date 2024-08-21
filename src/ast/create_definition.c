/**
 *
 * @file create_definition.c
 *
 * @brief Traverse AST for node create_definition.
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
 * create_definition
 *     : ('virtual' )? create_name var_decl_list function_body
 *     ;
 */
void traverse_create_definition(ast_create_definition_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


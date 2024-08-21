/**
 *
 * @file function_definition.c
 *
 * @brief Traverse AST for node function_definition.
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
 * function_definition
 *     : ('virtual' )? compound_name var_decl_list var_decl_list function_body
 *     ;
 */
void traverse_function_definition(ast_function_definition_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


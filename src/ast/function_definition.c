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

    TRACE("is_virtual = %s", node->is_virtual? "true": "false");
    traverse_compound_name(node->name, pre, post);
    traverse_var_decl_list(node->inp, pre, post);
    traverse_var_decl_list(node->outp, pre, post);
    traverse_function_body(node->body, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


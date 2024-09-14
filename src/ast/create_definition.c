/**
 *
 * @file create_definition.c
 *
 * @brief Traverse AST for node create_definition.
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
 * create_definition
 *     : ( function_membership )? 'create' func_parm_decl_list ( function_body )?
 *     ;
 */
void traverse_create_definition(ast_create_definition_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    traverse_function_membership(node->member, pre, post);
    traverse_func_parm_decl_list(node->inp, pre, post);
    traverse_function_body(node->body, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


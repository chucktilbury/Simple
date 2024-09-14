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
 *     : ( function_membership )? IDENT func_parm_decl_list func_parm_decl_list ( function_body )?
 *     ;
 */
void traverse_function_definition(ast_function_definition_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    //TRACE("is_iter = %s", node->is_iter? "true": "false");
    TRACE_TERMINAL(node->name);
    if(node->member != NULL)
        traverse_function_membership(node->member, pre, post);
    traverse_func_parm_decl_list(node->inp, pre, post);
    traverse_func_parm_decl_list(node->outp, pre, post);
    if(node->body != NULL)
        traverse_function_body(node->body, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


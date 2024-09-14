/**
 * @file func_parm_decl.c
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-09-13
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "ast.h"
#include "common.h"
#include "errors.h"
#include "trace.h"

/**
 * @brief
 *
 * func_parm_decl
 *     : typename ( IDENT )?
 *     ;
 *
 * @param node
 * @param pre
 * @param post
 */
void traverse_func_parm_decl(ast_func_parm_decl_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    traverse_type_name(node->type, pre, post);
    if(node->ident != NULL)
        TRACE_TERMINAL(node->ident);
    else
        TRACE("identity is not assigned");

    CALL_NODE_FUNC(post);
    RET;
}

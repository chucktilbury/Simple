/**
 * @file func_parm_decl_list.c
 * @author Chuck Tilbury (chucktilbury@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-09-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "common.h"
#include "trace.h"
#include "errors.h"
#include "ast.h"

/**
 * @brief 
 * 
 * func_parm_decl_list
 *     : '(' ( func_parm_decl ( ',' func_parm_decl )* )? ')'
 *     ;
 * 
 * @param node 
 * @param pre 
 * @param post 
 */
void traverse_func_parm_decl_list(ast_func_parm_decl_list_t* node, AstFuncPtr pre, AstFuncPtr post) {

     ENTER;
    CALL_NODE_FUNC(pre);

    ast_func_parm_decl_t* item;
    int mark = 0;

    TRACE("input list = %s", (node->inout)? "true": "false");
    while(NULL != (item = iterate_ptr_lst(node->list, &mark)))
        traverse_func_parm_decl(item, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


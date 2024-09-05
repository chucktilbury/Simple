/**
 *
 * @file var_decl_list.c
 *
 * @brief Traverse AST for node var_decl_list.
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
 * var_decl_list
 *     : '(' ( var_decl ( ',' var_decl )* )? ')'
 *     ;
 */
void traverse_var_decl_list(ast_var_decl_list_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);
    
    ast_var_decl_t* vd;
    int mark = 0;

    while(NULL != (vd = iterate_ptr_lst(node->list, &mark)))
        traverse_var_decl(vd, pre, post);
    
    CALL_NODE_FUNC(post);
    RET;
}


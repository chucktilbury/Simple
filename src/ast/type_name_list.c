/**
 *
 * @file type_name_list.c
 *
 * @brief Traverse AST for node type_name_list.
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
 * type_name_list
 *     : '(' ( type_name (',' type_name )* )? ')'
 *     ;
 */
void traverse_type_name_list(ast_type_name_list_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    ast_type_name_t* tn;
    int mark = 0;

    while(NULL != (tn = iterate_ptr_lst(node->list, &mark)))
        traverse_type_name(tn, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


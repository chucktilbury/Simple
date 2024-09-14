/**
 *
 * @file list_init.c
 *
 * @brief Traverse AST for node list_init.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "ast.h"
#include "common.h"
#include "errors.h"
#include "trace.h"

/**
 *
 * Grammar production:
 *
 * list_init
 *     : '[' list_init_element ( ',' list_init_element )* ']'
 *     ;
 */
void traverse_list_init(ast_list_init_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    ast_list_init_element_t* el;
    int mark = 0;

    while(NULL != (el = iterate_ptr_lst(node->list, &mark)))
        traverse_list_init_element(el, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}

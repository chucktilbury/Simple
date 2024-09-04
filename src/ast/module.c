/**
 *
 * @file module.c
 *
 * @brief Traverse AST for node module.
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
 * module
 *     : ( module_item )+
 *     ;
 */
void traverse_module(ast_module_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    ast_module_item_t* item = NULL;
    int mark = 0;
    while(NULL != (item = iterate_ptr_lst(node->list, &mark))) {
        traverse_module_item(item, pre, post);
    }

    CALL_NODE_FUNC(post);
    RET;
}


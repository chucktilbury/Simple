/**
 * @file class_inheritance_list.c
 * @author your name (chucktilbury@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-09-10
 *
 * @copyright Copyright (c) 2024
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
 * class_inheritance_list
 *     : '(' ( class_inheritance_item (',' class_inheritance_item)* )? ')'
 *     ;
 *
 */
void traverse_class_inheritance_list(ast_class_inheritance_list_t* node,
                                     AstFuncPtr pre,
                                     AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    ast_class_inheritance_item_t* item;
    int mark = 0;

    while(NULL != (item = iterate_ptr_lst(node->list, &mark)))
        traverse_class_inheritance_item(item, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}

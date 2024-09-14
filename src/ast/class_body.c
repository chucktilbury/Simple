/**
 *
 * @file class_definition_body.c
 *
 * @brief Traverse AST for node class_definition.
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
 * class_body
    : '{' ( class_body_item )+'}'
 *     ;
 */
void traverse_class_body(ast_class_body_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    ast_class_body_item_t* it;
    int mark = 0;

    while(NULL != (it = iterate_ptr_lst(node->list, &mark)))
        traverse_class_body_item(it, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}

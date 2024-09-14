/**
 * @file class_inheritance_item.c
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
 * class_inheritance_item
 *     : (scope_operator)? compound_name 'as' IDENT
 *     ;
 *
 */
void traverse_class_inheritance_item(ast_class_inheritance_item_t* node,
                                     AstFuncPtr pre,
                                     AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    traverse_scope_operator(node->scope, pre, post);
    traverse_compound_name(node->name, pre, post);
    TRACE_TERMINAL(node->ident);

    CALL_NODE_FUNC(post);
    RET;
}

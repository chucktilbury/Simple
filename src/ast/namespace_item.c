/**
 *
 * @file namespace_item.c
 *
 * @brief Traverse AST for node namespace_item.
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
 * namespace_item
 *     : scope_operator
 *     | namespace_definition
 *     | class_definition
 *     | function_definition
 *     | create_definition
 *     | destroy_definition
 *     | var_definition
 *     ;
 */
void traverse_namespace_item(ast_namespace_item_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


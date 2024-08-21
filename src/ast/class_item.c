/**
 *
 * @file class_item.c
 *
 * @brief Traverse AST for node class_item.
 * This file was generated on Wed Aug 21 09:35:58 2024.
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
 * class_item
 *     : scope_operator
 *     | var_decl
 *     | function_declaration
 *     | create_declaration
 *     | destroy_declaration
 *     ;
 */
void traverse_class_item(ast_class_item_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


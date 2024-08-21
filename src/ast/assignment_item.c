/**
 *
 * @file assignment_item.c
 *
 * @brief Traverse AST for node assignment_item.
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
 * assignment_item
 *     : expression
 *     | list_init
 *     | function_assignment
 *     ;
 */
void traverse_assignment_item(ast_assignment_item_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


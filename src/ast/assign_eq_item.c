/**
 *
 * @file assign_eq_item.c
 *
 * @brief Traverse AST for node assign_eq_item.
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
 * assign_eq_item
 *     : assignment_item
 *     | compound_reference
 *     ;
 */
void traverse_assign_eq_item(ast_assign_eq_item_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


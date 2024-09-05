/**
 *
 * @file assign_eq_item.c
 *
 * @brief Traverse AST for node assign_eq_item.
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
 * assign_eq_item
 *     : assignment_item
 *     | compound_reference
 *     ;
 */
void traverse_assign_eq_item(ast_assign_eq_item_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    switch(nterm_type(node->ptr)) {
        case AST_ASSIGNMENT_ITEM:
            traverse_assignment_item((ast_assignment_item_t*)(node->ptr), pre, post);
            break;
        case AST_COMPOUND_REFERENCE:
            traverse_compound_reference((ast_compound_reference_t*)(node->ptr), pre, post);
            break;
        default:
            FATAL("unknown ast node type: %s", nterm_type_to_str(node->ptr));
    }

    CALL_NODE_FUNC(post);
    RET;
}


/**
 *
 * @file compound_ref_item.c
 *
 * @brief Traverse AST for node compound_ref_item.
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
 * compound_ref_item
 *     : IDENT
 *     | array_reference
 *     ;
 */
void traverse_compound_ref_item(ast_compound_ref_item_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    if(node->name != NULL)
        TRACE_TERMINAL(node->name);
    else
        traverse_array_reference(node->ref, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}

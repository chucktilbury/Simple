/**
 *
 * @file compound_ref_item.c
 *
 * @brief Traverse AST for node compound_ref_item.
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
 * compound_ref_item
 *     : IDENT
 *     | array_reference
 *     ;
 */
void traverse_compound_ref_item(ast_compound_ref_item_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


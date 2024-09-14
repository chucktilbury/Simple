/**
 *
 * @file compound_reference.c
 *
 * @brief Traverse AST for node compound_reference.
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
 * compound_reference
 *     : compound_ref_item ( '.' compound_ref_item )*
 *     ;
 */
void traverse_compound_reference(ast_compound_reference_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    ast_compound_ref_item_t* ref;
    int mark = 0;

    while(NULL != (ref = iterate_ptr_lst(node->list, &mark)))
        traverse_compound_ref_item(ref, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}

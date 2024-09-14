/**
 *
 * @file array_reference.c
 *
 * @brief Traverse AST for node array_reference.
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
 * array_reference
 *     : IDENT array_param_list
 *     ;
 */
void traverse_array_reference(ast_array_reference_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    TRACE_TERMINAL(node->ident);
    traverse_array_param_list(node->list, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}

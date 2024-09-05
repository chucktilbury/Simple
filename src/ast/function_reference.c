/**
 *
 * @file function_reference.c
 *
 * @brief Traverse AST for node function_reference.
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
 * function_reference
 *     : compound_reference expression_list compound_name_list
 *     ;
 */
void traverse_function_reference(ast_function_reference_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    traverse_compound_reference(node->name, pre, post);
    traverse_expression_list(node->inp, pre, post);
    traverse_compound_name_list(node->outp, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


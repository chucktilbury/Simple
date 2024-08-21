/**
 *
 * @file function_reference.c
 *
 * @brief Traverse AST for node function_reference.
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
 * function_reference
 *     : compound_reference expression_list compound_name_list
 *     ;
 */
void traverse_function_reference(ast_function_reference_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


/**
 *
 * @file function_assignment.c
 *
 * @brief Traverse AST for node function_assignment.
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
 * function_assignment
 *     : compound_reference type_name_list type_name_list
 *     ;
 */
void traverse_function_assignment(ast_function_assignment_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


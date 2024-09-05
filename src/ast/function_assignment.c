/**
 *
 * @file function_assignment.c
 *
 * @brief Traverse AST for node function_assignment.
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
 * function_assignment
 *     : compound_reference type_name_list type_name_list
 *     ;
 */
void traverse_function_assignment(ast_function_assignment_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    traverse_compound_reference(node->name, pre, post);
    traverse_type_name_list(node->inp, pre, post);
    traverse_type_name_list(node->outp, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


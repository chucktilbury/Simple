/**
 *
 * @file assignment.c
 *
 * @brief Traverse AST for node assignment.
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
 * assignment
 *     : compound_reference '=' assign_eq_item
 *     | compound_reference '+=' assign_inc_item
 *     | compound_reference '-=' expression
 *     | compound_reference '*=' expression
 *     | compound_reference '/=' expression
 *     | compound_reference '%=' expression
 *     ;
 */
void traverse_assignment(ast_assignment_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


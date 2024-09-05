/**
 *
 * @file assignment.c
 *
 * @brief Traverse AST for node assignment.
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

    traverse_compound_reference(node->lhs, pre, post);
    TRACE_TERMINAL(node->oper);
    switch(nterm_type(node->rhs)) {
        case AST_ASSIGN_EQ_ITEM:
            traverse_assign_eq_item((ast_assign_eq_item_t*)(node->rhs), pre, post);
            break;
        case AST_ASSIGN_INC_ITEM:
            traverse_assign_inc_item((ast_assign_inc_item_t*)(node->rhs), pre, post);
            break;
        case AST_EXPRESSION:
            traverse_expression((ast_expression_t*)(node->rhs), pre, post);
            break;
        default:
            FATAL("unknown ast node type: %s", nterm_type_to_str(node->rhs));
    }

    CALL_NODE_FUNC(post);
    RET;
}


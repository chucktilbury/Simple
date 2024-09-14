/**
 *
 * @file expression.c
 *
 * @brief Traverse AST for node expression.
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
 * expression
 *     : expr_or
 *     ;
 */
void traverse_expression(ast_expression_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    TRACE("node type = %d", node->result_type);

    ast_node_t* item;
    int mark = 0;

    while(NULL != (item = iterate_ptr_lst(node->list, &mark))) {
        switch(nterm_type(item)) {
            case AST_EXPR_OPERAND:
                traverse_expr_operand((ast_expr_operand_t*)item, pre, post);
                break;
            case AST_EXPR_OPERATOR:
                traverse_expr_operator((ast_expr_operator_t*)item, pre, post);
                break;
            default:
                FATAL("unknown ast node type: %s", nterm_type_to_str(item));
        }
    }

    CALL_NODE_FUNC(post);
    RET;
}

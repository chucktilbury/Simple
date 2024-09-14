/**
 *
 * @file expr_primary.c
 *
 * @brief Traverse AST for node expr_primary.
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
 * expr_operand
 *     : literal_value
 *     | compound_reference
 *     | cast_statement
 *     ;
 */
void traverse_expr_operand(ast_expr_operand_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    switch(nterm_type(node->ptr)) {
        case AST_LITERAL_VALUE:
            traverse_literal_value((ast_literal_value_t*)(node->ptr), pre, post);
            break;
        case AST_COMPOUND_REFERENCE:
            traverse_compound_reference((ast_compound_reference_t*)(node->ptr), pre, post);
            break;
        case AST_CAST_STATEMENT:
            traverse_cast_statement((ast_cast_statement_t*)(node->ptr), pre, post);
            break;
        default:
            FATAL("unknown ast node type: %s", nterm_type_to_str(node->ptr));
    }

    CALL_NODE_FUNC(post);
    RET;
}

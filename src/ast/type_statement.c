/**
 *
 * @file type_statement.c
 *
 * @brief Traverse AST for node type_statement.
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
 * type_statement
 *     : 'type' '(' compound_reference ')'
 *     ;
 */
void traverse_type_statement(ast_type_statement_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    traverse_compound_reference(node->arg, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}

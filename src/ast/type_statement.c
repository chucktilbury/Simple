/**
 *
 * @file type_statement.c
 *
 * @brief Traverse AST for node type_statement.
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
 * type_statement
 *     : 'type' '(' compound_reference ')'
 *     ;
 */
void traverse_type_statement(ast_type_statement_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


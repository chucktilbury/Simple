/**
 *
 * @file while_definition.c
 *
 * @brief Traverse AST for node while_definition.
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
 * while_definition
 *     : 'while' ( '(' ( expression )? ')' )?
 *     ;
 */
void traverse_while_definition(ast_while_definition_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


/**
 *
 * @file var_definition.c
 *
 * @brief Traverse AST for node var_definition.
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
 * var_definition
 *     : ( 'const' )? var_decl ( '=' assignment_item )?
 *     ;
 */
void traverse_var_definition(ast_var_definition_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


/**
 *
 * @file var_definition.c
 *
 * @brief Traverse AST for node var_definition.
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
 * var_definition
 *     : ( 'const' )? var_decl ( '=' assignment_item )?
 *     ;
 */
void traverse_var_definition(ast_var_definition_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    TRACE("is_const = %s", node->is_const? "true": "false");
    traverse_var_decl(node->decl, pre, post);
    if(node->item != NULL)
        traverse_assignment_item(node->item, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


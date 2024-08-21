/**
 *
 * @file class_definition.c
 *
 * @brief Traverse AST for node class_definition.
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
 * class_definition
 *     : 'class' IDENT ( '(' ( type_name )? ')' )? '{' ( class_item )+ '}'
 *     ;
 */
void traverse_class_definition(ast_class_definition_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


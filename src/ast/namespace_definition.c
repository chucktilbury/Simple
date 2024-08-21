/**
 *
 * @file namespace_definition.c
 *
 * @brief Traverse AST for node namespace_definition.
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
 * namespace_definition
 *     : 'namespace' IDENT '{' ( namespace_item )+ '}'
 *     ;
 */
void traverse_namespace_definition(ast_namespace_definition_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


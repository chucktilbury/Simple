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

    TRACE_TERMINAL(node->name);
    ast_namespace_item_t* it;
    int mark = 0;

    while(NULL != (it = iterate_ptr_lst(node->items, &mark)))
        traverse_namespace_item(it, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


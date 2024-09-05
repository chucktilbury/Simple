/**
 *
 * @file class_definition.c
 *
 * @brief Traverse AST for node class_definition.
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
 * class_definition
    : 'class' IDENT ( '(' ( type_name 'as' IDENT )? ')' )? '{' ( class_item )+ '}'
 *     ;
 */
void traverse_class_definition(ast_class_definition_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    TRACE_TERMINAL(node->name);
    if(node->inher != NULL) {
        traverse_compound_name(node->inher, pre, post);
        TRACE_TERMINAL(node->as_name);
    }

    ast_class_item_t* it;
    int mark = 0;

    while(NULL != (it = iterate_ptr_lst(node->list, &mark)))
        traverse_class_item(it, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


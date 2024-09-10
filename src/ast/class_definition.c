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
    : 'class' IDENT ( class_inheritance_list )? class_body
 *     ;
 */
void traverse_class_definition(ast_class_definition_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    TRACE_TERMINAL(node->name);

    if(node->inher != NULL)
        traverse_class_inheritance_list(node->inher, pre, post);

    traverse_class_body(node->body, pre, post);

    CALL_NODE_FUNC(post);
    RET;
}


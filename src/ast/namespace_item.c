/**
 *
 * @file namespace_item.c
 *
 * @brief Traverse AST for node namespace_item.
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
 * namespace_item
 *     : scope_operator
 *     | namespace_definition
 *     | class_definition
 *     | function_definition
 *     | create_definition
 *     | destroy_definition
 *     | var_definition
 *     ;
 */
void traverse_namespace_item(ast_namespace_item_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    switch(nterm_type(node->ptr)) {
        case AST_SCOPE_OPERATOR:
            traverse_scope_operator((ast_scope_operator_t*)(node->ptr), pre, post);
            break;
        case AST_NAMESPACE_DEFINITION:
            traverse_namespace_definition((ast_namespace_definition_t*)(node->ptr), pre, post);
            break;
        case AST_CLASS_DEFINITION:
            traverse_class_definition((ast_class_definition_t*)(node->ptr), pre, post);
            break;
        case AST_FUNCTION_DEFINITION:
            traverse_function_definition((ast_function_definition_t*)(node->ptr), pre, post);
            break;
        case AST_CREATE_DEFINITION:
            traverse_create_definition((ast_create_definition_t*)(node->ptr), pre, post);
            break;
        case AST_DESTROY_DEFINITION:
            traverse_destroy_definition((ast_destroy_definition_t*)(node->ptr), pre, post);
            break;
        case AST_VAR_DEFINITION:
            traverse_var_definition((ast_var_definition_t*)(node->ptr), pre, post);
            break;
        default:
            FATAL("unknown ast node type: %s", nterm_type_to_str(node->ptr));
    }

    CALL_NODE_FUNC(post);
    RET;
}


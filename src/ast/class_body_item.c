/**
 *
 * @file class_body_item.c
 *
 * @brief Traverse AST for node class_body_item.
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
 * class_body_item
 *     : scope_operator
 *     | var_decl
 *     | function_declaration
 *     | create_declaration
 *     | destroy_declaration
 *     ;
 */
void traverse_class_body_item(ast_class_body_item_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    switch(nterm_type(node->ptr)) {
        case AST_SCOPE_OPERATOR:
            traverse_scope_operator((ast_scope_operator_t*)(node->ptr), pre, post);
            break;
        case AST_VAR_DECL:
            traverse_var_decl((ast_var_decl_t*)(node->ptr), pre, post);
            break;
        case AST_FUNCTION_DECLARATION:
            traverse_function_declaration((ast_function_declaration_t*)(node->ptr), pre, post);
            break;
        case AST_CREATE_DECLARATION:
            traverse_create_declaration((ast_create_declaration_t*)(node->ptr), pre, post);
            break;
        case AST_DESTROY_DECLARATION:
            traverse_destroy_declaration((ast_destroy_declaration_t*)(node->ptr), pre, post);
            break;
        default:
            FATAL("unknown ast node type: %s", nterm_type_to_str(node->ptr));
    }

    CALL_NODE_FUNC(post);
    RET;
}


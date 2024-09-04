/**
 *
 * @file module_item.c
 *
 * @brief Traverse AST for node module_item.
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
 * module_item
 *     : namespace_item
 *     | import_statement
 *     | include_statement
 *     | start_definition
 *     ;
 */
void traverse_module_item(ast_module_item_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    switch(nterm_type(node->ptr)) {
        case AST_NAMESPACE_ITEM:
            traverse_namespace_item((ast_namespace_item_t*)(node->ptr), pre, post);
            break;
        case AST_IMPORT_STATEMENT:
            traverse_import_statement((ast_import_statement_t*)(node->ptr), pre, post);
            break;
        case AST_INCLUDE_STATEMENT:
            traverse_include_statement((ast_include_statement_t*)(node->ptr), pre, post);
            break;
        case AST_START_DEFINITION:
            traverse_start_definition((ast_start_definition_t*)(node->ptr), pre, post);
            break;
        default:
            FATAL("unknown ast node type: %s", nterm_type_to_str(node->ptr));
    }

    CALL_NODE_FUNC(post);
    RET;
}


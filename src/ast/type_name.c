/**
 *
 * @file type_name.c
 *
 * @brief Traverse AST for node type_name.
 * This file was generated on Wed Aug 21 11:39:59 2024.
 *
 */
#include "ast.h"
#include "common.h"
#include "errors.h"
#include "trace.h"

/**
 *
 * Grammar production:
 *
 * type_name
 *     : literal_type_name
 *     | compound_name
 *     ;
 */
void traverse_type_name(ast_type_name_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    switch(nterm_type(node->ptr)) {
        case AST_LITERAL_TYPE_NAME:
            traverse_literal_type_name((ast_literal_type_name_t*)(node->ptr), pre, post);
            break;
        case AST_COMPOUND_NAME:
            traverse_compound_name((ast_compound_name_t*)(node->ptr), pre, post);
            break;
        default:
            FATAL("unknown ast node type: %s", nterm_type_to_str(node->ptr));
    }

    CALL_NODE_FUNC(post);
    RET;
}

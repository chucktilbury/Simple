/**
 *
 * @file literal_type_name.c
 *
 * @brief Traverse AST for node literal_type_name.
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
 * literal_type_name
 *     : 'float'
 *     | 'integer'
 *     | 'string'
 *     | 'boolean'
 *     | 'nothing'
 *     | 'list'
 *     | 'dict'
 *     ;
 */
void traverse_literal_type_name(ast_literal_type_name_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    TRACE_TERMINAL(node->tok);

    CALL_NODE_FUNC(post);
    RET;
}

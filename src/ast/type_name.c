/**
 *
 * @file type_name.c
 *
 * @brief Traverse AST for node type_name.
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
 * type_name
 *     : literal_type_name
 *     | compound_name
 *     ;
 */
void traverse_type_name(ast_type_name_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


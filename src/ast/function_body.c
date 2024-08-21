/**
 *
 * @file function_body.c
 *
 * @brief Traverse AST for node function_body.
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
 * function_body
 *     : '{' ( function_body_element )* '}'
 *     ;
 */
void traverse_function_body(ast_function_body_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


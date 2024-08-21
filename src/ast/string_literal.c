/**
 *
 * @file string_literal.c
 *
 * @brief Traverse AST for node string_literal.
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
 * string_literal
 *     : LITERAL_SSTR
 *     | formatted_strg
 *     ;
 */
void traverse_string_literal(ast_string_literal_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    CALL_NODE_FUNC(post);
    RET;
}


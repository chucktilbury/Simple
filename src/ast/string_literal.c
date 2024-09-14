/**
 *
 * @file string_literal.c
 *
 * @brief Traverse AST for node string_literal.
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
 * string_literal
 *     : LITERAL_SSTR
 *     | formatted_strg
 *     ;
 */
void traverse_string_literal(ast_string_literal_t* node, AstFuncPtr pre, AstFuncPtr post) {

    ENTER;
    CALL_NODE_FUNC(pre);

    if(node->fstr != NULL)
        traverse_formatted_strg(node->fstr, pre, post);

    TRACE_TERMINAL(node->lstr);

    CALL_NODE_FUNC(post);
    RET;
}
